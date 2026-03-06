#pragma once
#include "../game_state.h"
#include "../Module.h"
#include "../ModuleCategory.h"
#include "../../config/CheckboxValue.h"
#include "../../config/FloatSliderValue.h"
#include "../../il2cpp/Il2CppObjectInstance.h"

static bool do_speed;

using fixed_update_sig = void(*)(Il2CppObject*);
static fixed_update_sig o_player_camera_controller_fixed_update = nullptr;

inline void hk_player_camera_controller_fixed_update(Il2CppObject* instance)
{
    if (do_speed)
    {
        Il2CppObjectInstance controller_instance(instance);
        Il2CppObjectInstance main_player(controller_instance.get_method<Il2CppObject*(
            *)(Il2CppObject*)>("get_Player", 0)(instance));
        Il2CppObjectInstance character_controller(main_player.get_field<Il2CppObject*>("_characterController"));
        unity::vector3 velocity = character_controller.get_method<unity::vector3(*)(Il2CppObject*)>("get_velocity", 0)(
            character_controller.get_instance());
        velocity.x /= 100;
        velocity.y = 0;
        velocity.z /= 100;
        character_controller.get_method<int(*)(Il2CppObject*, unity::vector3, float)>("Move", 2)(
            character_controller.get_instance(), velocity, 100.0f);
    }

    o_player_camera_controller_fixed_update(instance);
}

class PlayerModule : Module
{
public:
    PlayerModule() : Module("Player", Exploit)
    {
    }

    CheckboxValue* speed_hack = conf(new CheckboxValue(false, "Speed Hack"));

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObjectInstance game_world_instance,
                          Il2CppObjectInstance main_player) override
    {
        do_speed = speed_hack->get_value();
    }

    void init() override
    {
        const Il2CppImage* image = il2utils::resolve_image("Assembly-CSharp.dll");

        // need a fixed update here so speed hack is consistent, this is a good one i found with access to player
        const Il2CppClass* player_camera_controller_class = il2utils::resolve_class(
            image, "EFT.CameraControl", "PlayerCameraController");
        il2utils::hook_method(player_camera_controller_class, "FixedUpdate", 0,
                              hk_player_camera_controller_fixed_update,
                              &o_player_camera_controller_fixed_update);
    }
};
