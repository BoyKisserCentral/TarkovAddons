#include <iostream>
#include <windows.h>

#include "assets/asset_bundles.h"
#include "gui/dxhook/dxhook.h"
#include "hooks/hooks.h"
#include "il2cpp/unity.h"
#include "module/always_on.h"
#include "module/common_hooks.h"
#include "module/ModuleManager.h"
#include "util/globals.h"
#include "util/logger.h"

namespace
{
    FILE* console = nullptr;

    void show_console()
    {
        AllocConsole();
        errno_t _ = freopen_s(&console, "CONOUT$", "w", stdout);
        SetConsoleTitleA(std::string(globals::get_display_title() + " | " + globals::credits).c_str());
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
        logger::info(globals::credits);

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

        // init unity interop
        logger::info("Loading Unity");
        unity::init();
        logger::info("Unity Loaded");

        // dxhook and menu
        logger::info("Hooking Present");
        if (!dxhook::init()) logger::error("Present Hook Failed");
        else logger::info("Hooked Present");

        // init modules
        logger::info("Loading Modules");
        ModuleManager::get_instance()->init();
        logger::info("Loaded Modules");

        // load default features and common hooks
        logger::info("Loading Default Features");
        always_on::init();
        common_hooks::init();
        logger::info("Loaded Default Features");

        std::cout << "\n";
        logger::warn(
            "This is FREE software! If you paid for this software or completed some task to obtain it, you were scammed!");
        std::cout << "\n";
        logger::info("Menu Key: Insert");
        std::cout << "\n";

        // eject will be back once ldr unlink attempt is added
        ExitThread(0);

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


        // shut down menu
        logger::info("Unhooked Present");
        dxhook::shutdown();

        // shut down imgui
        logger::info("Shutdown ImGui");
        dxhook::shutdown_imgui();

        // unhook all
        logger::info("Unhooked All");
        hooks::unhook_all();

        // delete modulemanager
        delete ModuleManager::get_instance();

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
