#pragma once
#include <string>

#include "../il2cpp/Il2CppObjectInstance.h"

namespace player_utils
{
    static bool is_networked_player_pmc(Il2CppObjectInstance* player)
    {
        return player->get_method<int(*)(Il2CppObject*)>("get_Side", 0)(player->get_instance()) != 4;
    }

    static std::string get_networked_player_name(Il2CppObjectInstance* player)
    {
        const int player_id = player->get_method<int(*)(Il2CppObject*)>("get_Id", 0)(player->get_instance());
        return (is_networked_player_pmc(player) ? "Player " : "Scav ")
            + std::to_string(player_id);
    }
}
