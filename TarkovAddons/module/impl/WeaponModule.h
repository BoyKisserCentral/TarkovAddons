#pragma once
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
    CheckboxValue* no_recoil = conf(new CheckboxValue(false, "No Recoil"));
    CheckboxValue* no_sway = conf(new CheckboxValue(false, "No Sway"));

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObjectInstance game_world_instance,
                          Il2CppObjectInstance main_player) override
    {
        Il2CppObject* hands_controller_object = main_player.get_method<Il2CppObject*(
            *)(Il2CppObject*)>("get_HandsController", 0)(main_player.get_instance());
        if (hands_controller_object && std::string(hands_controller_object->klass->name) == "FirearmController")
        {
            if (no_jam->get_value())
            {
                Il2CppObjectInstance firearm_controller(hands_controller_object);
                Il2CppObjectInstance weapon(
                    firearm_controller.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Item", 0)(
                        firearm_controller.get_instance()));
                Il2CppObjectInstance weapon_template(
                    weapon.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Template", 0)(weapon.get_instance()));

                weapon_template.set_field("AllowOverheat", false);
                weapon_template.set_field("AllowJam", false);
                weapon_template.set_field("AllowMisfire", false);
                weapon_template.set_field("AllowSlide", false);
                weapon_template.set_field("AllowFeed", false);
                weapon_template.set_field("DurabilityBurnRatio", 0.0f);
            }

            Il2CppObjectInstance procedural_weapon_animation(
                main_player.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_ProceduralWeaponAnimation", 0)(
                    main_player.get_instance()));

            const auto shot_effect_ptr = procedural_weapon_animation.get_field<Il2CppObject*>("Shootingg");
            const auto breath_effect_ptr = procedural_weapon_animation.get_field<Il2CppObject*>("Breath");
            const auto walk_effect_ptr = procedural_weapon_animation.get_field<Il2CppObject*>("Walk");

            if (no_recoil->get_value() && shot_effect_ptr)
            {
                logger::info("no recoil");
                procedural_weapon_animation.set_field("Mask", 1);
                Il2CppObjectInstance shot_effect(shot_effect_ptr);
                shot_effect.set_field("Intensity", 0.f);
            }

            if (no_sway->get_value() && breath_effect_ptr && walk_effect_ptr)
            {
                logger::info("no sway");
                Il2CppObjectInstance breath_effect(breath_effect_ptr);
                breath_effect.set_field("Intensity", 0.f);
                Il2CppObjectInstance walk_effect(walk_effect_ptr);
                walk_effect.set_field("Intensity", 0.f);
            }
        }
    }

    void init() override
    {
    }
};
