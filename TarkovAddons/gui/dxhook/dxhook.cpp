#include "dxhook.h"

#include <cstdint>

#include "../menu/menu.h"
#include <Windows.h>

#include <detours/detours.h>

#include "../../util/logger.h"

// method based on kiero hook

namespace
{
    inline bool initDone = false;
    inline LRESULT (*oWndProc)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    inline void (*oExecuteCommandLists)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*);
    inline HRESULT (*oPresent11)(void* pSwapChain, UINT SyncInterval, UINT Flags);
    inline HRESULT (*oPresent12)(void* pSwapChain, UINT SyncInterval, UINT Flags);

    int PRESENT_INDEX_11 = 8;
    int PRESENT_INDEX_12 = 140;
    int LIST_INDEX = 54;

    ID3D11Device* p_device11 = nullptr;
    ID3D11DeviceContext* p_context11 = nullptr;
    ID3D11RenderTargetView* main_render_target_view11 = nullptr;

    ID3D12Device* p_device12 = nullptr;
    ID3D12DescriptorHeap* p_descriptor_heap = nullptr;
    ID3D12DescriptorHeap* g_pd3d_rtv_desc_heap = nullptr;
    ID3D12DescriptorHeap* g_pd3d_srv_desc_heap = nullptr;
    ID3D12GraphicsCommandList* p_command_list = nullptr;
    ID3D12Resource** back_buffers = nullptr;
    D3D12_CPU_DESCRIPTOR_HANDLE* descriptor_handles = nullptr;
    ID3D12CommandAllocator* p_allocator = nullptr;
    ID3D12CommandQueue* p_command_queue = nullptr;
    D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle;
    UINT bufferCount = 0;

    bool is_dx12 = false;
    UINT64* g_methods_table = nullptr;
    HWND imgui_window = nullptr;
}

// yeah imgui is missing this for some reason
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI dxhook::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (!menu::is_active())
    {
        return CallWindowProcW(oWndProc, GetActiveWindow(), msg, wParam, lParam);
    }
    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
    return true;
}

bool dxhook::init()
{
    // create a window
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = DefWindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandle(nullptr);
    windowClass.hIcon = nullptr;
    windowClass.hCursor = nullptr;
    windowClass.hbrBackground = nullptr;
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = L"DXWindow";
    windowClass.hIconSm = nullptr;
    ::RegisterClassEx(&windowClass);
    HWND window = ::CreateWindow(windowClass.lpszClassName, L"DXWindow", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL,
                                 NULL, windowClass.hInstance, NULL);

    return dx12_setup(windowClass, window) || dx11_setup(windowClass, window);
}


bool dxhook::dx12_setup(const WNDCLASSEX& window_class, HWND window)
{
    // dx 12 setup
    // get all needed instances and api
    HMODULE lib_dxgi;
    HMODULE lib_d_3d12;
    if ((lib_dxgi = ::GetModuleHandle(L"dxgi.dll")) == nullptr || (lib_d_3d12 = ::GetModuleHandle(L"d3d12.dll")) ==
        nullptr)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    void* CreateDXGIFactory;
    if ((CreateDXGIFactory = GetProcAddress(lib_dxgi, "CreateDXGIFactory")) == nullptr) // NOLINT(clang-diagnostic-microsoft-cast)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    IDXGIFactory* factory;
    if (reinterpret_cast<long(__stdcall*)(const IID&, void**)>(CreateDXGIFactory)(
        __uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory)) < 0) // NOLINT(clang-diagnostic-language-extension-token)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    IDXGIAdapter* adapter;
    if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    void* D3D12CreateDevice;
    if ((D3D12CreateDevice = GetProcAddress(lib_d_3d12, "D3D12CreateDevice")) == nullptr) // NOLINT(clang-diagnostic-microsoft-cast)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    ID3D12Device* device;
    if (reinterpret_cast<long(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**)>(D3D12CreateDevice)(
        adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), reinterpret_cast<void**>(&device)) < 0) // NOLINT(clang-diagnostic-language-extension-token)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    D3D12_COMMAND_QUEUE_DESC queue_desc;
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queue_desc.Priority = 0;
    queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queue_desc.NodeMask = 0;

    ID3D12CommandQueue* command_queue;
    if (device->CreateCommandQueue(&queue_desc, __uuidof(ID3D12CommandQueue), reinterpret_cast<void**>(&command_queue)) < // NOLINT(clang-diagnostic-language-extension-token)
        0)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    ID3D12CommandAllocator* command_allocator;
    if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), // NOLINT(clang-diagnostic-language-extension-token)
                                       reinterpret_cast<void**>(&command_allocator)) < 0)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    ID3D12GraphicsCommandList* command_list;
    if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator, nullptr,
                                  __uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&command_list)) < 0) // NOLINT(clang-diagnostic-language-extension-token)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    // set up our swapchain
    DXGI_RATIONAL refresh_rate;
    refresh_rate.Numerator = 60;
    refresh_rate.Denominator = 1;

    DXGI_MODE_DESC buffer_desc;
    buffer_desc.Width = 100;
    buffer_desc.Height = 100;
    buffer_desc.RefreshRate = refresh_rate;
    buffer_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    buffer_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    buffer_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    DXGI_SAMPLE_DESC sample_desc;
    sample_desc.Count = 1;
    sample_desc.Quality = 0;

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    swapChainDesc.BufferDesc = buffer_desc;
    swapChainDesc.SampleDesc = sample_desc;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = window;
    swapChainDesc.Windowed = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain* swap_chain;
    if (factory->CreateSwapChain(command_queue, &swapChainDesc, &swap_chain) < 0)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    // yoink the method table
    g_methods_table = static_cast<UINT64*>(calloc(150, sizeof(UINT64)));
    memcpy(g_methods_table, *reinterpret_cast<UINT64**>(device), 44 * sizeof(UINT64));
    memcpy(g_methods_table + 44, *reinterpret_cast<UINT64**>(command_queue), 19 * sizeof(UINT64));
    memcpy(g_methods_table + 44 + 19, *reinterpret_cast<UINT64**>(command_allocator), 9 * sizeof(UINT64));
    memcpy(g_methods_table + 44 + 19 + 9, *reinterpret_cast<UINT64**>(command_list), 60 * sizeof(UINT64));
    memcpy(g_methods_table + 44 + 19 + 9 + 60, *reinterpret_cast<UINT64**>(swap_chain), 18 * sizeof(UINT64));

    // we dont need this stuff now
    device->Release();
    device = nullptr;

    command_queue->Release();
    command_queue = nullptr;

    command_allocator->Release();
    command_allocator = nullptr;

    command_list->Release();
    command_list = nullptr;

    swap_chain->Release();
    swap_chain = nullptr;

    DestroyWindow(window);
    ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);

    auto target_present = reinterpret_cast<PVOID*>(g_methods_table[PRESENT_INDEX_12]); // NOLINT(performance-no-int-to-ptr)
    auto target_execute_command_lists = reinterpret_cast<PVOID*>(g_methods_table[LIST_INDEX]); // NOLINT(performance-no-int-to-ptr)

    oPresent12 = reinterpret_cast<HRESULT (*)(void*, UINT, UINT)>(target_present);
    oExecuteCommandLists = reinterpret_cast<void (*)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*)>(
        target_execute_command_lists);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    // ReSharper disable once CppCStyleCast
    DetourAttach(&(PVOID&)(oPresent12), reinterpret_cast<PVOID>(dxPresent12));
    // ReSharper disable once CppCStyleCast
    DetourAttach(&(PVOID&)(oExecuteCommandLists), reinterpret_cast<PVOID>(executeCommandLists12));

    if (DetourTransactionCommit() != NO_ERROR)
    {
        free(g_methods_table);
        g_methods_table = nullptr;
        return false;
    }

    // init done
    return true;
}

bool dxhook::dx11_setup(const WNDCLASSEX& window_class, HWND window)
{
    // dx 11 setup
    // get all needed instances and api
    HMODULE lib_d_3d11;
    if ((lib_d_3d11 = ::GetModuleHandle(L"d3d11.dll")) == nullptr)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    void* d_3d11_create_device_and_swap_chain;
    if ((d_3d11_create_device_and_swap_chain = reinterpret_cast<void*>(GetProcAddress(
        lib_d_3d11, "D3D11CreateDeviceAndSwapChain"))) == nullptr)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    // set up our swapchain
    D3D_FEATURE_LEVEL feature_level;
    constexpr D3D_FEATURE_LEVEL feature_levels[] = {D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0};

    DXGI_RATIONAL refresh_rate11;
    refresh_rate11.Numerator = 60;
    refresh_rate11.Denominator = 1;

    DXGI_MODE_DESC buffer_desc11;
    buffer_desc11.Width = 100;
    buffer_desc11.Height = 100;
    buffer_desc11.RefreshRate = refresh_rate11;
    buffer_desc11.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    buffer_desc11.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    buffer_desc11.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    DXGI_SAMPLE_DESC sample_desc11;
    sample_desc11.Count = 1;
    sample_desc11.Quality = 0;

    DXGI_SWAP_CHAIN_DESC swap_chain_desc11;
    swap_chain_desc11.BufferDesc = buffer_desc11;
    swap_chain_desc11.SampleDesc = sample_desc11;
    swap_chain_desc11.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc11.BufferCount = 1;
    swap_chain_desc11.OutputWindow = window;
    swap_chain_desc11.Windowed = 1;
    swap_chain_desc11.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc11.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain* swap_chain11;
    ID3D11Device* device11;
    ID3D11DeviceContext* context11;

    if (reinterpret_cast<long(__stdcall*)(
        IDXGIAdapter*,
        D3D_DRIVER_TYPE,
        HMODULE,
        UINT,
        const D3D_FEATURE_LEVEL*,
        UINT,
        UINT,
        const DXGI_SWAP_CHAIN_DESC*,
        IDXGISwapChain**,
        ID3D11Device**,
        D3D_FEATURE_LEVEL*,
        ID3D11DeviceContext**)>(d_3d11_create_device_and_swap_chain)(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
                                                                     feature_levels, 2, D3D11_SDK_VERSION,
                                                                     &swap_chain_desc11,
                                                                     &swap_chain11, &device11, &feature_level,
                                                                     &context11) < 0)
    {
        DestroyWindow(window);
        ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return false;
    }

    // yoink the method table
    g_methods_table = static_cast<UINT64*>(calloc(205, sizeof(UINT64)));
    memcpy(g_methods_table, *reinterpret_cast<UINT64**>(swap_chain11), 18 * sizeof(UINT64));
    memcpy(g_methods_table + 18, *reinterpret_cast<UINT64**>(device11), 43 * sizeof(UINT64));
    memcpy(g_methods_table + 18 + 43, *reinterpret_cast<UINT64**>(context11), 144 * sizeof(UINT64));

    // we dont need this stuff now
    swap_chain11->Release();
    swap_chain11 = nullptr;

    device11->Release();
    device11 = nullptr;

    context11->Release();
    context11 = nullptr;

    DestroyWindow(window);
    ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);

    // hook present func
    auto target = reinterpret_cast<PVOID*>(g_methods_table[PRESENT_INDEX_11]); // NOLINT(performance-no-int-to-ptr)
    oPresent11 = reinterpret_cast<HRESULT (*)(void*, UINT, UINT)>(target);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    // ReSharper disable once CppCStyleCast
    DetourAttach(&(PVOID&)(oPresent11), reinterpret_cast<PVOID>(dxPresent11));

    if (DetourTransactionCommit() != NO_ERROR)
    {
        return false;
    }

    // init done
    return true;
}

void dxhook::shutdown()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    // ReSharper disable once CppCStyleCast
    DetourDetach(&(PVOID&)(oPresent11), reinterpret_cast<PVOID>(dxPresent11));
    // ReSharper disable once CppCStyleCast
    DetourDetach(&(PVOID&)(oPresent12), reinterpret_cast<PVOID>(dxPresent12));
    // ReSharper disable once CppCStyleCast
    DetourDetach(&(PVOID&)(oExecuteCommandLists), reinterpret_cast<PVOID>(executeCommandLists12));

    DetourTransactionCommit();
    free(g_methods_table);
    g_methods_table = nullptr;
}

void __fastcall dxhook::executeCommandLists12(ID3D12CommandQueue* p_command_queue1, UINT num_command_lists,
                                              ID3D12CommandList* const * pp_command_lists)
{
    if (!p_command_queue)
    {
        p_command_queue = p_command_queue1;
    }
    oExecuteCommandLists(p_command_queue1, num_command_lists, pp_command_lists);
}

HRESULT __fastcall dxhook::dxPresent11(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags)
{
    // init imgui first time
    if (!initDone)
    {
        if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&p_device11)))) // NOLINT(clang-diagnostic-language-extension-token)
        {
            is_dx12 = false;
            p_device11->GetImmediateContext(&p_context11);
            DXGI_SWAP_CHAIN_DESC sd;
            p_swap_chain->GetDesc(&sd);
            imgui_window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer)); // NOLINT(clang-diagnostic-language-extension-token)
            p_device11->CreateRenderTargetView(pBackBuffer, nullptr, &main_render_target_view11);
            pBackBuffer->Release();
            oWndProc = reinterpret_cast<LRESULT(*)(HWND, UINT, WPARAM, LPARAM)>(SetWindowLongPtr( // NOLINT(performance-no-int-to-ptr)
                imgui_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));

            // Init Imgui
            init_imgui();

            initDone = true;
        }
        else
        {
            is_dx12 = true;
        }
    }

    // draw imgui ui
    if (!is_dx12) draw_imgui(nullptr);

    return oPresent11(p_swap_chain, sync_interval, flags);
}

HRESULT __fastcall dxhook::dxPresent12(IDXGISwapChain3* p_swap_chain, UINT sync_interval, UINT flags)
{
    // init imgui first time
    if (!initDone)
    {
        if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(&p_device12)))) // NOLINT(clang-diagnostic-language-extension-token)
        {
            is_dx12 = true;
            DXGI_SWAP_CHAIN_DESC sd;
            p_swap_chain->GetDesc(&sd);
            imgui_window = sd.OutputWindow;

            DXGI_SWAP_CHAIN_DESC swapChainDesc;
            bufferCount = p_swap_chain->GetDesc(&swapChainDesc);
            bufferCount = swapChainDesc.BufferCount;

            p_device12->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&p_allocator));
            p_device12->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, p_allocator, nullptr,
                                          IID_PPV_ARGS(&p_command_list));
            p_command_list->Close();

            p_device12->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
            D3D12_DESCRIPTOR_HEAP_DESC desc;
            desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            desc.NumDescriptors = bufferCount;
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
            desc.NodeMask = 1;
            p_device12->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3d_rtv_desc_heap));
            SIZE_T rtvDescriptorSize = p_device12->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
            rtv_handle = g_pd3d_rtv_desc_heap->GetCPUDescriptorHandleForHeapStart();
            back_buffers = new ID3D12Resource*[bufferCount];
            descriptor_handles = new D3D12_CPU_DESCRIPTOR_HANDLE[bufferCount];
            for (UINT i = 0; i < bufferCount; i++)
            {
                ID3D12Resource* pBackBuffer = nullptr;
                p_swap_chain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
                p_device12->CreateRenderTargetView(pBackBuffer, nullptr, rtv_handle);
                back_buffers[i] = pBackBuffer;
                descriptor_handles[i] = rtv_handle;
                rtv_handle.ptr += rtvDescriptorSize;
            }

            oWndProc = reinterpret_cast<LRESULT(*)(HWND, UINT, WPARAM, LPARAM)>(SetWindowLongPtr( // NOLINT(performance-no-int-to-ptr)
                imgui_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));

            // Init Imgui
            init_imgui();

            initDone = true;
        }
        else
        {
            is_dx12 = false;
        }
    }

    // draw imgui ui
    if (is_dx12) draw_imgui(p_swap_chain);

    return oPresent12(p_swap_chain, sync_interval, flags);
}

void dxhook::init_imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplWin32_Init(imgui_window);
    if (is_dx12)
    {
        D3D12_DESCRIPTOR_HEAP_DESC descriptor = {};
        descriptor.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        descriptor.NumDescriptors = bufferCount;
        descriptor.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        p_device12->CreateDescriptorHeap(&descriptor, IID_PPV_ARGS(&p_descriptor_heap));
        ImGui_ImplDX12_Init(p_device12, 2, DXGI_FORMAT_R8G8B8A8_UNORM, p_descriptor_heap,
                            p_descriptor_heap->GetCPUDescriptorHandleForHeapStart(),
                            p_descriptor_heap->GetGPUDescriptorHandleForHeapStart());
    }
    else
    {
        ImGui_ImplDX11_Init(p_device11, p_context11);
    }

    menu::setup();

    initDone = true;
}

void dxhook::shutdown_imgui()
{
    initDone = false;

    if (is_dx12)
    {
        ImGui_ImplDX12_Shutdown();
    }
    else
    {
        ImGui_ImplDX11_Shutdown();
    }
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    if (oWndProc != nullptr)
    {
        SetWindowLongPtr(imgui_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
    }
    if (is_dx12)
    {
        p_descriptor_heap->Release();
        g_pd3d_srv_desc_heap->Release();
        p_allocator->Release();
        p_command_list->Release();
        for (size_t i = 0; i < bufferCount; ++i)
        {
            back_buffers[i]->Release();
        }
        delete[] back_buffers;
        delete[] descriptor_handles;
    }
    else
    {
        main_render_target_view11->Release();
    }
}

void dxhook::draw_imgui(IDXGISwapChain3* p_swap_chain)
{
    if (is_dx12)
    {
        ImGui_ImplDX12_NewFrame();
    }
    else
    {
        ImGui_ImplDX11_NewFrame();
    }
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    {
        menu::draw();
    }
    ImGui::EndFrame();
    ImGui::Render();

    if (is_dx12)
    {
        size_t index = p_swap_chain->GetCurrentBackBufferIndex();
        ID3D12Resource* p_back_buffer = back_buffers[index];
        p_allocator->Reset();
        D3D12_RESOURCE_BARRIER barrier;
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        barrier.Transition.pResource = p_back_buffer;
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        p_command_list->Reset(p_allocator, nullptr);
        p_command_list->ResourceBarrier(1, &barrier);
        p_command_list->OMSetRenderTargets(1, &descriptor_handles[index], FALSE, nullptr);
        p_command_list->SetDescriptorHeaps(1, &p_descriptor_heap);
        ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), p_command_list);
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        p_command_list->ResourceBarrier(1, &barrier);
        p_command_list->Close();

        // skip if we cont have the queue right now
        if (p_command_queue == nullptr) return;
        p_command_queue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&p_command_list));
    }
    else
    {
        p_context11->OMSetRenderTargets(1, &main_render_target_view11, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}
