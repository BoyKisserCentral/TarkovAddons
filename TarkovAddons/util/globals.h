#pragma once
#include <string>

namespace globals
{
    const std::string prod_name("TarkovAddons");
    const std::string prod_ver("v0.1");
    constexpr bool console = true;
    constexpr bool verbose = false;

    static std::string get_display_title()
    {
        return prod_name + " " + prod_ver;
    }
}
