#pragma once
#include "../eft_api.h"
#include "../game_state.h"
#include "../Module.h"
#include "../ModuleCategory.h"
#include "../../config/CheckboxValue.h"
#include "../../config/FloatSliderValue.h"
#include "../../il2cpp/Il2CppObjectInstance.h"

class PlayerModule : Module
{
public:
    PlayerModule() : Module("Player", Exploit)
    {
    }

    CheckboxValue* god_mode = conf(new CheckboxValue(false, "God Mode"));
    CheckboxValue* infinite_stamina = conf(new CheckboxValue(false, "Infinite Stamina"));
    CheckboxValue* no_hunger = conf(new CheckboxValue(false, "No Hunger"));
    CheckboxValue* no_thirst = conf(new CheckboxValue(false, "No Thirst"));
    CheckboxValue* instant_search = conf(new CheckboxValue(false, "Instant Search"));

    SelectValue* exp_type = conf(new SelectValue(0, {
                                                     "ExpDoorBreached", "ExpItemLooting", "ExpDamage", "ExpHeal",
                                                     "ExpExamine", "ExpKillBase", "ExpItemLooting"
                                                 }, "Exp Type"));
    IntSliderValue* exp_amount = conf(new IntSliderValue(10000, 0, 500000, "Exp Amount"));
    ActionRowValue* add_exp = conf(new ActionRowValue([&]
    {
        add_exp_impl();
    }, "Add Exp"));

    SelectValue* fence_rep_source = conf(new SelectValue(0, {
                                                             "Boss Help", "Scav Help", "Scav Kill", "Boss Kill",
                                                             "Traitor Kill", "Exit Standing"
                                                         }, "Fence Rep Source"));
    FloatSliderValue* fence_rep_amount = conf(new FloatSliderValue(0.1f, 0, 5, "Fence Rep Amount"));
    ActionRowValue* add_fence_rep = conf(new ActionRowValue([&]
    {
        add_fence_rep_impl();
    }, "Add Fence Rep"));

    SelectValue* trader_select = conf(new SelectValue(0, {
                                                          "LIGHT_KEEPER_TRADER", "RAGMAN_TRADER",
                                                          "ARENA_MANAGER_TRADER", "PEACEKEEPER", "SKIER",
                                                          "PRAPOR_TRADER", "JAEGER_TRADER", "MECHANIC_TRADER",
                                                          "TERAPEVT_TRADER"
                                                      }, "Trader"));
    FloatSliderValue* trader_rep_amount = conf(new FloatSliderValue(0.1f, 0, 5, "Trader Rep Amount"));
    ActionRowValue* add_trader_rep = conf(new ActionRowValue([&]
    {
        add_trader_rep_impl();
    }, "Add Trader Rep"));


    bool queue_add_exp = false;
    bool queue_add_fence_rep = false;
    bool queue_add_trader_rep = false;

    void add_exp_impl()
    {
        if (!game_state::is_in_raid) return;
        queue_add_exp = true;
    }

    void add_fence_rep_impl()
    {
        if (!game_state::is_in_raid) return;
        queue_add_fence_rep = true;
    }

    void add_trader_rep_impl()
    {
        if (!game_state::is_in_raid) return;
        queue_add_trader_rep = true;
    }

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObject* game_world) override
    {
        // no player outside of raid
        if (!game_state::is_in_raid) return;

        const auto game_world_instance = new Il2CppObjectInstance(game_world);
        const auto main_player_object = game_world_instance->get_field<Il2CppObject*>("MainPlayer");

        // if player is not loaded yet
        if (main_player_object == nullptr) return;

        const auto main_player = new Il2CppObjectInstance(main_player_object);

        const auto get_profile = main_player->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Profile", 0);
        const auto main_profile = new Il2CppObjectInstance(get_profile(main_player->get_instance()));

        if (infinite_stamina->get_value())
        {
            const auto physical = new Il2CppObjectInstance(main_player->get_field<Il2CppObject*>("Physical"));

            const auto stamina = new Il2CppObjectInstance(physical->get_field<Il2CppObject*>("Stamina"));
            stamina->set_field("Current", 100.0f);

            const auto stamina_hands = new Il2CppObjectInstance(physical->get_field<Il2CppObject*>("HandsStamina"));
            stamina_hands->set_field("Current", 100.0f);

            const auto oxygen = new Il2CppObjectInstance(physical->get_field<Il2CppObject*>("Oxygen"));
            oxygen->set_field("Current", 100.0f);
        }

        const auto health_controller = new Il2CppObjectInstance(
            main_player->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_ActiveHealthController", 0)(
                main_player->get_instance()));
        if (god_mode->get_value())
        {
            health_controller->get_method<void(*)(Il2CppObject*, float)>("SetDamageCoeff", 1)(
                health_controller->get_instance(), -1.0f);
            health_controller->get_method<void(*)(Il2CppObject*, int)>("RemoveNegativeEffects", 1)(
                health_controller->get_instance(), 7); // 7 = Common
            health_controller->get_method<void(*)(Il2CppObject*)>("RestoreFullHealth", 0)(
                health_controller->get_instance());
            health_controller->get_method<void(*)(Il2CppObject*)>("DoPainKiller", 0)(
                health_controller->get_instance());
            health_controller->set_field("_fallSafeHeight", 99999999.0f);
        }

        if (no_hunger->get_value())
        {
            health_controller->get_method<void(*)(Il2CppObject*, float)>("ChangeEnergy", 1)(
                health_controller->get_instance(), 100.0f);
        }

        if (no_thirst->get_value())
        {
            health_controller->get_method<void(*)(Il2CppObject*, float)>("ChangeHydration", 1)(
                health_controller->get_instance(), 100.0f);
        }

        const auto skill_manager = new Il2CppObjectInstance(
            main_player->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Skills", 0)(main_player->get_instance()));
        if (instant_search->get_value())
        {
            auto attention_elite_lucky_search = new Il2CppObjectInstance(
                skill_manager->get_field<Il2CppObject*>("AttentionEliteLuckySearch"));

            attention_elite_lucky_search->set_field("Value", 100000.0f);
        }

        if (queue_add_exp)
        {
            queue_add_exp = false;
            const auto eft_stats = new Il2CppObjectInstance(
                main_profile->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_EftStats", 0)(
                    main_profile->get_instance()));

            auto session_counters = new Il2CppObjectInstance(eft_stats->get_field<Il2CppObject*>("SessionCounters"));

            const Il2CppImage* assembly_csharp = il2utils::resolve_image("Assembly-CSharp.dll");
            const Il2CppClass* predefined_counters = il2utils::resolve_class(assembly_csharp, "EFT.Counters",
                                                                             "PredefinedCounters");
            const auto reason = il2utils::get_static_field<Il2CppObject
                *>(predefined_counters, exp_type->get_selected().c_str());

            session_counters->get_method<void(*)(Il2CppObject*, int, Il2CppObject*)>("AddInt", 2)(
                session_counters->get_instance(), exp_amount->get_value(), reason);
        }

        if (queue_add_fence_rep)
        {
            queue_add_fence_rep = false;
            const auto loyalty_data = new Il2CppObjectInstance(
                main_player->get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Loyalty", 0)(
                    main_player->get_instance()));

            loyalty_data->get_method<void(*)(Il2CppObject*, double, int)>("KillAsSavage", 2)(
                loyalty_data->get_instance(), fence_rep_amount->get_value(), fence_rep_source->get_value());
        }

        if (queue_add_trader_rep)
        {
            queue_add_trader_rep = false;
            std::string trader_id_key = trader_select->get_selected() + "_ID";

            const Il2CppClass* profile_class = il2utils::resolve_class(game_world_class->image, "EFT", "Profile");
            const Il2CppClass* trader_info_class = il2utils::resolve_class_nested(profile_class, "TraderInfo");
            const auto trader_id = il2utils::get_static_field<Il2CppString*>(trader_info_class, trader_id_key.c_str());
            const auto try_get_trader_info = il2utils::get_method<bool(
                *)(Il2CppObject*, Il2CppString*, Il2CppObject**)>(
                profile_class, "TryGetTraderInfo", 2);

            Il2CppObject* trader_info = nullptr;
            if (try_get_trader_info(main_profile->get_instance(), trader_id, &trader_info) && trader_info)
            {
                const auto trader_info_instance = new Il2CppObjectInstance(trader_info);

                const double standing = trader_info_instance->get_method<double(*)(Il2CppObject*)>("get_Standing", 0)(
                    trader_info);

                trader_info_instance->get_method<void(*)(Il2CppObject*, double)>("SetStanding", 1)(
                    trader_info, trader_rep_amount->get_value() + standing);
            }
        }
    }

    void init() override
    {
    }
};
