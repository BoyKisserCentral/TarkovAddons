#include <iostream>
#include <windows.h>

#include "gui/dxhook/dxhook.h"
#include "hooks/hooks.h"
#include "il2cpp/il2cpp_offsets.h"
#include "util/globals.h"
#include "util/logger.h"

namespace
{
    FILE* console = nullptr;

    void show_console()
    {
        AllocConsole();
        errno_t _ = freopen_s(&console, "CONOUT$", "w", stdout);
        SetConsoleTitleA(globals::get_display_title().c_str());
    }

    void hide_console()
    {
        errno_t _ = fclose(console);
        FreeConsole();
    }

    [[noreturn]] void init(HMODULE this_module)
    {
        // alloc console
        if (globals::console) show_console();

        logger::info(globals::get_display_title());

        // wait for GameAssembly.dll to load
        logger::info("Waiting for GameAssembly.dll");
        while (!GetModuleHandleA("GameAssembly.dll"))
        {
            Sleep(50);
        }

        // load il2cpp offsets
        il2cpp_offsets::init();

        // wait for dx window
        while (!GetModuleHandle(L"d3d11.dll") && !(GetModuleHandle(L"d3d12.dll") && GetModuleHandle(L"dxgi.dll")))
        {
            Sleep(50);
        }

        // dxhook and menu
        logger::info("Hooking Present");
        if (!dxhook::init()) logger::error("Present Hook Failed");
        else logger::info("Hooked Present");

        // wait for eject input
        while (true)
        {
            Sleep(50);
            if (GetAsyncKeyState(VK_DELETE) & 1)
            {
                logger::info("Ejecting");
                break;
            }
        }

        // TODO: fix eject
        dxhook::shutdown();
        logger::info("Unhooked Present");
        dxhook::shutdown_imgui();
        logger::info("Shutdown ImGui");
        hooks::unhook_all();
        logger::info("Unhooked All");
        if (globals::console) hide_console();
        FreeLibraryAndExitThread(this_module, 0);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), hModule, 0, nullptr); // NOLINT(clang-diagnostic-cast-function-type-strict)
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    default: ;
    }

    return TRUE;
}
