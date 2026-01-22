#pragma once
#include "../eft_api.h"
#include "../game_state.h"
#include "../../config/IntSliderValue.h"
#include "../../il2cpp/il2utils.h"
#include "../../il2cpp/Il2CppObjectInstance.h"
#include "../../il2cpp/unity.h"

class EspModule : Module
{
public:
    EspModule() : Module("ESP", Visuals)
    {
    }

    CheckboxValue* extracts = conf(new CheckboxValue(false, "Extracts"));
    ColorpickerValue* extracts_color = conf(new ColorpickerValue({0, 1, 0, 1}, "Extract Color"));

    CheckboxValue* transits = conf(new CheckboxValue(false, "Transits"));
    ColorpickerValue* transits_color = conf(new ColorpickerValue({1, 1, 0, 1}, "Transit Color"));

    CheckboxValue* players = conf(new CheckboxValue(false, "Players"));
    ColorpickerValue* player_color = conf(new ColorpickerValue({1, 0, 0, 1}, "Player Color"));
    CheckboxValue* npc = conf(new CheckboxValue(false, "NPC"));
    ColorpickerValue* npc_color = conf(new ColorpickerValue({1, 1, 0, 1}, "NPC Color"));

    IntSliderValue* font_size = conf(new IntSliderValue(12, 8, 36, "Font Size"));

    enum class player_type : char
    {
        pmc,
        npc,
    };

    struct exfil
    {
        std::string name;
        int status;
        unity::vector3 pos3d;
    };

    struct transit
    {
        std::string name;
        unity::vector3 pos3d;
    };

    struct player
    {
        std::string name;
        bool pmc;
        unity::vector3 pos3d;
    };

    unity::vector3 my_pos = {};

    std::vector<exfil> exfil_store = std::vector<exfil>();
    std::vector<transit> transits_store = std::vector<transit>();
    std::vector<player> player_store = std::vector<player>();

    void draw_overlay(ImDrawList* draw_list) override
    {
        // no esp outside of raid
        if (!game_state::is_in_raid) return;

        // find cameras
        Il2CppObject* cam = unity::get_current_camera();
        // Il2CppObject* scope_cam = unity::get_named_camera("BaseOpticCamera(Clone)");

        // extract esp
        if (extracts->get_value())
        {
            for (const auto& [name, status, pos3d] : exfil_store)
            {
                unity::vector3 screen_pos = eft_api::world_to_screen(cam, pos3d, game_state::current_zoom);
                if (!eft_api::is_visible(screen_pos)) continue;
                const float distance = my_pos.distance(pos3d);

                std::string status_string;
                switch (status)
                {
                case 8:
                    status_string = "Hidden";
                    break;
                case 7:
                    status_string = "Inactive";
                    break;
                case 6:
                    status_string = "Pending";
                    break;
                case 5:
                case 4:
                    status_string = "Open";
                    break;
                case 2:
                    status_string = "Available";
                    break;
                case 1:
                    status_string = "Closed";
                    break;
                default:
                    status_string = "Unknown";
                    break;
                }

                std::string text = std::string("[").append(std::to_string(static_cast<int>(distance))).append("m] ").
                                                    append(name).append(" (").append(status_string).append(")");

                imgui_addons::centered_text(draw_list, menu::get_hud_font(),
                                            static_cast<float>(font_size->get_value()) * menu::get_scale_factor(),
                                            {screen_pos.x, screen_pos.y}, extracts_color->get_value(), text);
            }
        }

        // transit esp
        if (transits->get_value())
        {
            for (const auto& [name, pos3d] : transits_store)
            {
                unity::vector3 screen_pos = eft_api::world_to_screen(cam, pos3d, game_state::current_zoom);
                if (!eft_api::is_visible(screen_pos)) continue;
                const float distance = my_pos.distance(pos3d);
                std::string text = std::string("[").append(std::to_string(static_cast<int>(distance))).append("m] ").
                                                    append(name);

                imgui_addons::centered_text(draw_list, menu::get_hud_font(),
                                            static_cast<float>(font_size->get_value()) * menu::get_scale_factor(),
                                            {screen_pos.x, screen_pos.y}, transits_color->get_value(), text);
            }
        }

        // player esp
        if (players->get_value())
        {
            for (const auto& [name, pmc, pos3d] : player_store)
            {
                unity::vector3 screen_pos = eft_api::world_to_screen(cam, pos3d, game_state::current_zoom);
                if (!eft_api::is_visible(screen_pos)) continue;
                const float distance = my_pos.distance(pos3d);
                std::string text = std::string("[").append(std::to_string(static_cast<int>(distance))).append("m] ").
                                                    append(name);

                switch (pmc) // NOLINT(clang-diagnostic-switch-bool)
                {
                case true:
                    if (!players->get_value()) break;
                    imgui_addons::centered_text(draw_list, menu::get_hud_font(),
                                                static_cast<float>(font_size->get_value()) * menu::get_scale_factor(),
                                                {screen_pos.x, screen_pos.y + 10 * menu::get_scale_factor()},
                                                player_color->get_value(), text);
                    break;
                case false:
                    if (!npc->get_value()) break;
                    imgui_addons::centered_text(draw_list, menu::get_hud_font(),
                                                static_cast<float>(font_size->get_value()) * menu::get_scale_factor(),
                                                {screen_pos.x, screen_pos.y + 10 * menu::get_scale_factor()},
                                                npc_color->get_value(), text);
                    break;
                }
            }
        }
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObjectInstance game_world_instance,
                          Il2CppObjectInstance main_player) override
    {
        const auto main_player_game_object = unity::component_get_game_object(main_player.get_instance());
        const auto main_player_transform = unity::gameobject_get_transform(main_player_game_object);
        my_pos = unity::transform_get_pos(main_player_transform);

        const auto get_profile = main_player.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Profile", 0);
        Il2CppObjectInstance main_profile(get_profile(main_player.get_instance()));

        const std::string main_nickname = eft_api::to_english(il2utils::conv_wstring(
            main_profile.get_method<Il2CppString*(*)(Il2CppObject*)>("get_Nickname", 0)(
                main_profile.get_instance())));

        // extract esp
        if (extracts->get_value())
        {
            Il2CppObjectInstance exfiltration_controller(
                game_world_instance.get_field<Il2CppObject*>(
                    "<ExfiltrationController>k__BackingField"));

            const auto exfils = exfiltration_controller.get_method<Il2CppArray*(
                *)(Il2CppObject*, Il2CppObject*)>("EligiblePoints", 1)(exfiltration_controller.get_instance(),
                                                                       main_profile.get_instance());

            auto new_exfils = std::vector<exfil>();
            for (size_t i = 0; i < exfils->max_length; ++i)
            {
                Il2CppObject* exfil = reinterpret_cast<Il2CppObject**>(&exfils->data)[i];
                if (!exfil) continue;
                Il2CppObjectInstance exfiltration_point(exfil);

                const int status = exfiltration_point.get_field<int>("_status");

                Il2CppObjectInstance exfil_settings(exfiltration_point.get_field<Il2CppObject*>("Settings"));

                const std::string name = il2utils::conv_string(exfil_settings.get_field<Il2CppString*>("Name"));

                Il2CppObject* game_object = unity::component_get_game_object(exfiltration_point.get_instance());
                Il2CppObject* tranform = unity::gameobject_get_transform(game_object);

                new_exfils.push_back({
                    .name = name, .status = status, .pos3d = unity::transform_get_pos(tranform)
                });
            }

            exfil_store = new_exfils;
        }

        // transit esp
        if (transits->get_value())
        {
            Il2CppObjectInstance transit_controller(
                game_world_instance.get_field<Il2CppObject*>("<TransitController>k__BackingField"));

            const auto transits_by_id = transit_controller.get_field<unity::dict<int, Il2CppObject*>*>("pointsById");

            auto new_transits = std::vector<transit>();

            for (int i = 0; i < transits_by_id->m_i_count; ++i)
            {
                Il2CppObjectInstance transit(transits_by_id->get_value_by_index(i));

                Il2CppObjectInstance parameters(transit.get_field<Il2CppObject*>("parameters"));

                const std::string location = il2utils::conv_string(parameters.get_field<Il2CppString*>("location"));

                Il2CppObject* transit_game_object = unity::component_get_game_object(transit.get_instance());
                Il2CppObject* transit_transform = unity::gameobject_get_transform(transit_game_object);

                new_transits.push_back({.name = location, .pos3d = unity::transform_get_pos(transit_transform)});
            }

            transits_store = new_transits;
        }

        // player esp
        auto new_players = std::vector<player>();
        if (players->get_value() || npc->get_value())
        {
            Il2CppArray* alive_players = game_world_instance.get_field<unity::list*>("AllAlivePlayersList")->
                                                             m_p_list_array;

            for (size_t i = 0; i < alive_players->max_length; ++i)
            {
                Il2CppObject* player_object =
                    reinterpret_cast<Il2CppObject**>(&alive_players->data)[i];
                if (!player_object) continue;
                Il2CppObjectInstance player_instance(player_object);

                Il2CppObjectInstance profile_instance(get_profile(player_instance.get_instance()));

                std::string nickname = eft_api::to_english(il2utils::conv_wstring(
                    profile_instance.get_method<Il2CppString*(*)(Il2CppObject*)>("get_Nickname", 0)(
                        profile_instance.get_instance())));

                // skip ourselves
                if (nickname == main_nickname) continue;

                Il2CppObject* player_game_object = unity::component_get_game_object(player_instance.get_instance());
                Il2CppObject* player_transform = unity::gameobject_get_transform(player_game_object);

                // check if player has a dogtag to see if it's a pmc, yes this is actually the best way i found to do this
                Il2CppObjectInstance inventory_controller(
                    player_instance.get_field<Il2CppObject*>("_inventoryController"));

                Il2CppObjectInstance inventory(
                    inventory_controller.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Inventory", 0)(
                        inventory_controller.get_instance()));

                Il2CppObjectInstance equipment(
                    inventory.get_field<Il2CppObject*>("Equipment"));

                // 13 = Dogtag
                Il2CppObjectInstance equipment_slot(
                    equipment.get_method<Il2CppObject*(*)(Il2CppObject*, int)>("GetSlot", 1)(
                        equipment.get_instance(), 13));

                Il2CppObject* item_ptr = equipment_slot.get_method<Il2CppObject*(*)(Il2CppObject*)>(
                    "get_ContainedItem", 0)(
                    equipment_slot.get_instance());

                new_players.push_back({
                    .name = nickname, .pmc = item_ptr != nullptr, .pos3d = unity::transform_get_pos(player_transform)
                });
            }

            player_store = new_players;
        }
    }

    void init() override
    {
    }
};
