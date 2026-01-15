#pragma once
#include <Windows.h>

namespace utils
{
    static void get_desktop_resolution(int& horizontal, int& vertical)
    {
        RECT desktop;
        const HWND hDesktop = GetDesktopWindow();
        GetWindowRect(hDesktop, &desktop);
        horizontal = desktop.right;
        vertical = desktop.bottom;
    }
}
