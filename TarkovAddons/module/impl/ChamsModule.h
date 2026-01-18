#pragma once
#include <set>

#include "../eft_api.h"
#include "../game_state.h"
#include "../../config/IntSliderValue.h"
#include "../../il2cpp/il2utils.h"
#include "../../il2cpp/Il2CppObjectInstance.h"
#include "../../il2cpp/unity.h"
#include "../Module.h"
#include "../../assets/asset_bundles.h"
#include "../../config/ColorpickerValue.h"
#include "../../config/SelectValue.h"

class ColorpickerValue;
class Module;
class IntSliderValue;

class ChamsModule : Module
{
public:
    ChamsModule() : Module("Chams", Visuals)
    {
    }

    CheckboxValue* player_chams = conf(new CheckboxValue(true, "Player Chams"));
    CheckboxValue* gear_chams = conf(new CheckboxValue(false, "Gear Chams"));
    SelectValue* chams_type = conf(new SelectValue(0, {"Solid", "Wireframe"}, "Type"));
    ColorpickerValue* visible_color = conf(new ColorpickerValue({0, 1, 0, 1}, "Visible Color"));
    ColorpickerValue* invisible_color = conf(new ColorpickerValue({1, 0, 0, 1}, "Invisible Color"));
    CheckboxValue* weapon_chams = conf(new CheckboxValue(true, "Weapon Chams"));
    SelectValue* weapon_chams_type = conf(new SelectValue(0, {"Solid", "Wireframe"}, "Weapon Type"));
    ColorpickerValue* weapon_chams_color = conf(new ColorpickerValue({.5, 0, .5, .5}, "Weapon Color"));
    CheckboxValue* include_scope = conf(new CheckboxValue(false, "Include Scope"));
    CheckboxValue* include_arms = conf(new CheckboxValue(true, "Include Arms"));

    std::set<size_t> applied_players = std::set<size_t>();

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObject* game_world) override
    {
        // no chams outside of raid
        if (!game_state::is_in_raid) return;

        const auto game_world_instance = new Il2CppObjectInstance(game_world_class, game_world);
        Il2CppObjectInstance* main_player = Il2CppObjectInstance::create(game_world_class->image, "EFT", "Player",
                                                                         game_world_instance->get_field<Il2CppObject*>(
                                                                             "MainPlayer"));

        // if player is not loaded yet
        if (main_player->get_instance() == nullptr) return;

        const Il2CppImage* unity_image = il2utils::resolve_image("UnityEngine.CoreModule.dll");

        const auto get_profile = main_player->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Profile", 0);
        Il2CppObjectInstance* main_profile = Il2CppObjectInstance::create(
            game_world_class->image, "EFT", "Profile",
            get_profile(main_player->get_instance()));

        const std::string main_nickname = eft_api::to_english(il2utils::conv_wstring(
            main_profile->get_method<Il2CppString*(*)(Il2CppObject*)>("get_Nickname", 0)(
                main_profile->get_instance())));

        // weapon chams
        if (weapon_chams->get_value())
        {
            Il2CppObject* renderer_type = il2utils::get_system_type(unity_image, "UnityEngine", "Renderer");
            const auto main_player_game_object = unity::component_get_game_object(main_player->get_instance());
            const auto main_player_transform = unity::gameobject_get_transform(main_player_game_object);
            std::vector<Il2CppObject*> renderers{};
            unity::transform_apply_to_all_children(main_player_transform,
                                                   [&renderer_type, &renderers](Il2CppObject* transform)
                                                   {
                                                       Il2CppObject* game_object = unity::transform_get_game_object(
                                                           transform);
                                                       renderers.push_back(
                                                           unity::get_component_internal(game_object, renderer_type));
                                                   });

            for (const auto renderer : renderers)
            {
                if (renderer == nullptr) continue;
                const auto renderer_instance = new Il2CppObjectInstance(renderer);

                Il2CppObjectInstance* material_instance = Il2CppObjectInstance::create(
                    unity_image, "UnityEngine", "Material",
                    renderer_instance->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_material", 0)(
                        renderer_instance->get_instance()));

                std::string name = unity::get_name(material_instance->get_instance());

                bool is_scope = name.find("scope") != std::string::npos || name.find("optic") != std::string::npos;
                bool is_arms = name.find("watch") != std::string::npos || name.find("bear") != std::string::npos || name
                    .find("Bear") != std::string::npos || name.find("usec") != std::string::npos || name.find("arm") !=
                    std::string::npos || name.find("Usec") != std::string::npos;

                if ((!is_scope || include_scope->get_value()) && (!is_arms || include_arms->get_value()))
                {
                    // load shader from assetbundle
                    if (!asset_bundles::asset_bundle) continue;
                    Il2CppObject* shader_system_type = il2utils::get_system_type(
                        unity_image, "UnityEngine", "Shader");
                    Il2CppObject* chams_shader;
                    switch (weapon_chams_type->get_value())
                    {
                    case 0:
                        chams_shader = asset_bundles::load_asset(
                            "chams.shader", shader_system_type);
                        break;
                    case 1:
                        chams_shader = asset_bundles::load_asset(
                            "wireframe.shader", shader_system_type);
                        break;
                    default:
                        chams_shader = nullptr;
                    }

                    material_instance->get_method<void(*)(Il2CppObject*, Il2CppObject*)>("set_shader", 1)(
                        material_instance->get_instance(), chams_shader);

                    Il2CppString* color_visible = il2cpp::il2cpp_string_new("_Color_Visible");
                    Il2CppString* color_occluded = il2cpp::il2cpp_string_new("_Color_Occluded");

                    const auto set_color = material_instance->get_method<void(*)(
                        Il2CppObject*, Il2CppString*, unity::color)>("SetColor", 2);

                    const ImVec4 visible = weapon_chams_color->get_value();
                    set_color(material_instance->get_instance(), color_visible,
                              unity::color{visible.x, visible.y, visible.z, visible.w});
                    set_color(material_instance->get_instance(), color_occluded,
                              unity::color{visible.x, visible.y, visible.z, visible.w});
                }
            }
        }

        // chams
        if (player_chams->get_value())
        {
            Il2CppArray* alive_players = game_world_instance->get_field<unity::list*>("AllAlivePlayersList")->
                                                              m_p_list_array;

            for (size_t i = 0; i < alive_players->max_length; ++i)
            {
                Il2CppObjectInstance* player_instance = Il2CppObjectInstance::create(
                    game_world_class->image, "EFT", "Player",
                    reinterpret_cast<Il2CppObject**>(&alive_players->data)[i]);

                if (!player_instance->get_instance()) continue;

                Il2CppObjectInstance* profile_instance = Il2CppObjectInstance::create(
                    game_world_class->image, "EFT", "Profile", get_profile(player_instance->get_instance()));

                std::string nickname = eft_api::to_english(il2utils::conv_wstring(
                    profile_instance->get_method<Il2CppString*(*)(Il2CppObject*)>("get_Nickname", 0)(
                        profile_instance->get_instance())));

                // skip ourselves
                if (nickname == main_nickname) continue;

                // re-apply when menu is open
                if (menu::is_active())
                {
                    applied_players.clear();
                }

                // skip already processed players
                if (applied_players.contains(Hash::get(nickname.c_str()))) continue;

                Il2CppObjectInstance* player_body = Il2CppObjectInstance::create(
                    game_world_class->image, "EFT", "PlayerBody",
                    player_instance->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_PlayerBody", 0)(
                        player_instance->get_instance()));

                const auto body_skins = player_body->get_field<unity::dict<int, Il2CppObject*>*>("BodySkins");

                for (int j = 0; j < body_skins->m_i_count; ++j)
                {
                    Il2CppObjectInstance* lodded_skin = Il2CppObjectInstance::create(
                        game_world_class->image, "EFT.Visual", "LoddedSkin", body_skins->get_value_by_index(j));

                    const auto lods_array = lodded_skin->get_field<Il2CppArray*>("_lods");
                    for (size_t k = 0; k < lods_array->max_length; ++k)
                    {
                        Il2CppObject* skin_object = reinterpret_cast<Il2CppObject**>(&lods_array->data)[k];
                        const auto abstract_skin_instance = new Il2CppObjectInstance(skin_object);

                        const auto skinned_mesh_renderer = new Il2CppObjectInstance(
                            abstract_skin_instance->get_method<Il2CppObject*(*)(Il2CppObject*)>(
                                "get_SkinnedMeshRenderer", 0)(abstract_skin_instance->get_instance())
                        );

                        Il2CppObjectInstance* material_instance = Il2CppObjectInstance::create(
                            unity_image, "UnityEngine", "Material",
                            skinned_mesh_renderer->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_material", 0)(
                                skinned_mesh_renderer->get_instance()));

                        std::string name = unity::get_name(material_instance->get_instance());
                        if (!(name.find("armour") != std::string::npos || name.find("helmet") != std::string::npos ||
                            name.find("glasses") != std::string::npos || name.find("cover") != std::string::npos ||
                            name.find("rig") != std::string::npos || name.find("belt") != std::string::npos || name.
                            find("wear") != std::string::npos || name.find("mask") != std::string::npos || name.
                            find("balaclava") != std::string::npos) || gear_chams->get_value())
                        {
                            // load shader from assetbundle
                            if (!asset_bundles::asset_bundle) continue;
                            Il2CppObject* shader_system_type = il2utils::get_system_type(
                                unity_image, "UnityEngine", "Shader");
                            Il2CppObject* chams_shader;
                            switch (chams_type->get_value())
                            {
                            case 0:
                                chams_shader = asset_bundles::load_asset(
                                    "chams.shader", shader_system_type);
                                break;
                            case 1:
                                chams_shader = asset_bundles::load_asset(
                                    "wireframe.shader", shader_system_type);
                                break;
                            default:
                                chams_shader = nullptr;
                            }

                            material_instance->get_method<void(*)(Il2CppObject*, Il2CppObject*)>("set_shader", 1)(
                                material_instance->get_instance(), chams_shader);

                            Il2CppString* color_visible = il2cpp::il2cpp_string_new("_Color_Visible");
                            Il2CppString* color_occluded = il2cpp::il2cpp_string_new("_Color_Occluded");

                            const auto set_color = material_instance->get_method<void(*)(
                                Il2CppObject*, Il2CppString*, unity::color)>("SetColor", 2);

                            const ImVec4 visible = visible_color->get_value();
                            const ImVec4 invisible = invisible_color->get_value();
                            set_color(material_instance->get_instance(), color_visible,
                                      unity::color{visible.x, visible.y, visible.z, visible.w});
                            set_color(material_instance->get_instance(), color_occluded,
                                      unity::color{invisible.x, invisible.y, invisible.z, invisible.w});
                        }
                    }
                }

                applied_players.insert(Hash::get(nickname.c_str()));
            }
        }
    }

    void init() override
    {
    }
};
