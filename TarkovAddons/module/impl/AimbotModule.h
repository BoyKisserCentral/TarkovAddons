#pragma once
#include "../eft_api.h"
#include "../game_state.h"
#include "../Module.h"
#include "../../config/ColorpickerValue.h"
#include "../../config/FloatSliderValue.h"
#include "../../config/IntSliderValue.h"
#include "../../config/KeybindValue.h"
#include "../../il2cpp/il2utils.h"
#include "../../il2cpp/Il2CppObjectInstance.h"
#include "../../il2cpp/unity.h"
#include "../../util/player_utils.h"

static unity::vector3 target_store = {};

class AimbotModule : Module
{
public:
    AimbotModule() : Module("Aimbot", Aimbot)
    {
    }

    CheckboxValue* aim = conf(new CheckboxValue(false, "Aim"));
    KeybindValue* aim_key = conf(new KeybindValue(VK_XBUTTON2, "Aim Key"));
    IntSliderValue* fov = conf(new IntSliderValue(200, 50, 400, "Fov"));
    CheckboxValue* show_fov = conf(new CheckboxValue(false, "Show Fov"));
    ColorpickerValue* fov_color = conf(new ColorpickerValue({1, 0, 1, 1}, "Fov Color"));
    CheckboxValue* vis_check = conf(new CheckboxValue(true, "Vis Check"));
    FloatSliderValue* smooth = conf(new FloatSliderValue(5, 1, 10, "Smooth"));
    CheckboxValue* show_target = conf(new CheckboxValue(true, "Show Target"));
    FloatSliderValue* target_size = conf(new FloatSliderValue(3, 1, 10, "Target Size"));
    ColorpickerValue* target_color = conf(new ColorpickerValue({1, 0, 1, 1}, "Target Color"));

    void draw_overlay(ImDrawList* draw_list) override
    {
        // no aimbot outside of raid
        if (!game_state::is_in_raid) return;

        // find cameras
        Il2CppObject* cam = unity::get_current_camera();

        // show target
        if (aim->get_value() && show_target->get_value())
        {
            if (!(target_store.x == 0 && target_store.y == 0)) // NOLINT(clang-diagnostic-float-equal)
                if (unity::vector3 screen_pos = eft_api::world_to_screen(cam, target_store, game_state::current_zoom);
                    eft_api::is_visible(screen_pos))
                {
                    draw_list->AddCircleFilled({screen_pos.x, screen_pos.y},
                                               target_size->get_value() * menu::get_scale_factor(),
                                               ImGui::GetColorU32(target_color->get_value()));
                }
        }

        // fov
        if (show_fov->get_value())
        {
            draw_list->AddCircle({menu::get_width() / 2, menu::get_height() / 2},
                                 static_cast<float>(fov->get_value()) * menu::get_scale_factor(),
                                 ImGui::GetColorU32(fov_color->get_value()));
        }
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObjectInstance game_world_instance,
                          Il2CppObjectInstance main_player) override
    {
        const auto get_profile = main_player.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Profile", 0);
        Il2CppObjectInstance main_profile(get_profile(main_player.get_instance()));

        const std::string main_nickname = eft_api::to_english(il2utils::conv_wstring(
            main_profile.get_method<Il2CppString*(*)(Il2CppObject*)>("get_Nickname", 0)(
                main_profile.get_instance())));

        // player esp
        if (aim->get_value())
        {
            // find cameras
            Il2CppObject* cam = unity::get_current_camera();

            const unity::vector3 screen_center = {menu::get_width() / 2, menu::get_height() / 2, 0};

            float closest = FLT_MAX;
            unity::vector3 closest_pos = {};

            Il2CppArray* alive_players = game_world_instance.get_field<unity::list*>("RegisteredPlayers")->
                                                             m_p_list_array;
            for (size_t i = 0; i < alive_players->max_length; ++i)
            {
                Il2CppObject* player_object =
                    reinterpret_cast<Il2CppObject**>(&alive_players->data)[i];
                if (!player_object) continue;
                Il2CppObjectInstance player_instance(player_object);

                Il2CppObject* profile_ptr = get_profile(player_instance.get_instance());
                std::string nickname;
                if (std::string(player_object->klass->name) == "ObservedPlayerView")
                {
                    nickname = player_utils::get_networked_player_name(&player_instance);
                }
                else
                {
                    Il2CppObjectInstance profile_instance(profile_ptr);
                    nickname = eft_api::to_english(il2utils::conv_wstring(
                        profile_instance.get_method<Il2CppString*(*)(Il2CppObject*)>("get_Nickname", 0)(
                            profile_instance.get_instance())));
                }

                // skip ourselves
                if (nickname == main_nickname) continue;

                // get head position
                Il2CppObjectInstance player_body(
                    player_instance.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_PlayerBody", 0)(player_object));
                Il2CppObjectInstance player_bones(player_body.get_field<Il2CppObject*>("PlayerBones"));
                Il2CppObjectInstance bifacial_transform_head(player_bones.get_field<Il2CppObject*>("Head"));
                const unity::vector3 head_pos = bifacial_transform_head.get_method<unity::vector3(
                    *)(Il2CppObject*)>("get_position", 0)(bifacial_transform_head.get_instance());
                unity::vector3 screen_pos = eft_api::world_to_screen(cam, head_pos, game_state::current_zoom);
                if (!eft_api::is_visible(screen_pos)) continue;
                screen_pos.z = 0;

                if (const float dist = screen_pos.distance(screen_center); dist < closest)
                {
                    closest_pos = head_pos;
                    closest = dist;
                }
            }

            target_store = closest_pos;
        }
        else
        {
            target_store = {};
        }
    }

    void init() override
    {
    }
};
