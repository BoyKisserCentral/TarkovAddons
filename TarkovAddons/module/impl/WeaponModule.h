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

    CheckboxValue* no_jam = conf(new CheckboxValue(false, "No Malfunction"));

    CheckboxValue* infinite_ammo = conf(new CheckboxValue(false, "Infinite Ammo"));

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObject* game_world) override
    {
        // no weapons outside of raid
        if (!game_state::is_in_raid) return;

        Il2CppObjectInstance game_world_instance(game_world);
        const auto main_player_object = game_world_instance.get_field<Il2CppObject*>("MainPlayer");

        // if player is not loaded yet
        if (main_player_object == nullptr) return;

        Il2CppObjectInstance main_player(main_player_object);

        if (no_jam->get_value() || infinite_ammo->get_value())
        {
            Il2CppObject* hands_controller_object = main_player.get_method<Il2CppObject*(
                *)(Il2CppObject*)>("get_HandsController", 0)(main_player.get_instance());

            if (hands_controller_object && std::string(hands_controller_object->klass->name) == "FirearmController")
            {
                Il2CppObjectInstance firearm_controller(hands_controller_object);
                Il2CppObjectInstance weapon(
                    firearm_controller.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Item", 0)(
                        firearm_controller.get_instance()));
                Il2CppObjectInstance templt(
                    weapon.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Template", 0)(weapon.get_instance()));

                if (no_jam->get_value())
                {
                    templt.set_field("AllowOverheat", false);
                    templt.set_field("AllowJam", false);
                    templt.set_field("AllowMisfire", false);
                    templt.set_field("AllowSlide", false);
                    templt.set_field("AllowFeed", false);
                    templt.set_field("DurabilityBurnRatio", 0.0f);
                }

                if (infinite_ammo->get_value())
                {
                    Il2CppObject* mag_object = weapon.get_method<Il2CppObject*(*)(Il2CppObject*)>(
                        "GetCurrentMagazine", 0)(
                        weapon.get_instance());
                    if (mag_object)
                    {
                        Il2CppObjectInstance magazine(mag_object);
                        int current_count = weapon.get_method<int(*)(Il2CppObject*)>("GetCurrentMagazineCount", 0)(
                            weapon.get_instance());
                        int max_count = weapon.get_method<int(*)(Il2CppObject*)>("GetMaxMagazineCount", 0)(
                            weapon.get_instance());

                        if (current_count != 0 && current_count < max_count)
                        {
                            Il2CppObjectInstance first_real_ammo(magazine.get_method<Il2CppObject*(*)(Il2CppObject*)>(
                                "FirstRealAmmo", 0)(magazine.get_instance()));

                            first_real_ammo.set_field("StackObjectsCount", max_count);

                            /*
                            Il2CppObjectInstance cartridges(
                                magazine.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Cartridges", 0)(
                                    magazine.get_instance()));

                            cartridges.get_method<Il2CppObject*(*)(Il2CppObject*, Il2CppObject*, bool)>("Add", 2)(
                                cartridges.get_instance(), first_real_ammo, false);
                                */
                        }
                    }
                }
            }
        }
    }

    void init() override
    {
    }
};
