#pragma once

// input, 11 and 12
# include <dxgi.h>
# include <dxgi1_4.h>
# include <d3d11.h>
# include <d3d12.h>

namespace dxhook
{
    LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    bool dx12_setup(const WNDCLASSEX& window_class, HWND window);
    bool dx11_setup(const WNDCLASSEX& window_class, HWND window);
    bool init();
    void shutdown();
    void __fastcall executeCommandLists12(ID3D12CommandQueue* p_command_queue1, UINT num_command_lists,
                                          ID3D12CommandList* const * pp_command_lists);
    HRESULT __fastcall dxPresent11(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags);
    HRESULT __fastcall dxPresent12(IDXGISwapChain3* p_swap_chain, UINT sync_interval, UINT flags);
    void init_imgui();
    void shutdown_imgui();
    void draw_imgui(IDXGISwapChain3* p_swap_chain);
}
