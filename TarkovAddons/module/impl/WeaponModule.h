#pragma once
#include "../eft_api.h"
#include "../game_state.h"
#include "../Module.h"
#include "../ModuleCategory.h"
#include "../../il2cpp/Il2CppObjectInstance.h"

class WeaponModule : Module
{
public:
    WeaponModule() : Module("Weapon", Exploit)
    {
    }

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObject* game_world) override
    {
        /*
        // no weapons outside of raid
        if (!game_state::is_in_raid) return;

        Il2CppObjectInstance game_world_instance(game_world);
        const auto main_player_object = game_world_instance.get_field<Il2CppObject*>("MainPlayer");

        // if player is not loaded yet
        if (main_player_object == nullptr) return;

        Il2CppObjectInstance main_player(main_player_object);

        const auto get_profile = main_player.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Profile", 0);
        Il2CppObjectInstance main_profile(get_profile(main_player.get_instance()));

        const std::string main_nickname = eft_api::to_english(il2utils::conv_wstring(
            main_profile.get_method<Il2CppString*(*)(Il2CppObject*)>("get_Nickname", 0)(
                main_profile.get_instance())));
                */
    }

    void init() override
    {
    }
};
