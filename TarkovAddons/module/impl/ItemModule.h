#pragma once
#include <chrono>
#include <random>

#include "../game_state.h"
#include "../Module.h"
#include "../ModuleCategory.h"
#include "../../config/TextboxValue.h"
#include "../../il2cpp/Il2CppObjectInstance.h"


static Il2CppObject* item_factory;
using init_level_sig = Il2CppObject*(*)(Il2CppObject*, Il2CppObject*, Il2CppObject*, bool, Il2CppObject*, Il2CppObject*,
                                        Il2CppObject*);
static init_level_sig o_init_level = nullptr;

inline Il2CppObject* hk_init_level(Il2CppObject* instance, Il2CppObject* item_factory_, Il2CppObject* config,
                                   const bool load_bundles_and_create_pools, Il2CppObject* resources,
                                   Il2CppObject* progress,
                                   Il2CppObject* ct)
{
    item_factory = item_factory_;
    return o_init_level(instance, item_factory_, config, load_bundles_and_create_pools, resources, progress, ct);
}

class ItemModule : Module
{
public:
    ItemModule() : Module("Item", Exploit)
    {
    }

    TextboxValue* item_id = conf(new TextboxValue("", "Item Id"));
    ActionRowValue* create_item = conf(new ActionRowValue([&]
    {
        create_item_impl();
    }, "Create Item"));

    bool queue_create_item = false;

    void create_item_impl()
    {
        if (!game_state::is_in_raid) return;
        queue_create_item = true;
    }

    static std::mt19937& get_rng()
    {
        static std::mt19937 rng(static_cast<uint32_t>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count()));
        return rng;
    }

    static std::string generate_mongo_id()
    {
        static constexpr char hex[] = "0123456789abcdef";
        std::uniform_int_distribution dist(0, 15);
        std::string out;
        out.reserve(24);
        for (int i = 0; i < 24; ++i)
        {
            out.push_back(hex[dist(get_rng())]);
        }
        return out;
    }

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void application_update() override
    {
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObject* game_world) override
    {
        // no items outside of raid
        if (!game_state::is_in_raid) return;

        Il2CppObjectInstance game_world_instance(game_world);
        const auto main_player_object = game_world_instance.get_field<Il2CppObject*>("MainPlayer");

        // if player is not loaded yet
        if (main_player_object == nullptr) return;

        Il2CppObjectInstance main_player(main_player_object);

        if (queue_create_item)
        {
            queue_create_item = false;
            if (!item_factory) return;

            Il2CppObjectInstance item_factory_instance(item_factory);
            const auto create_item_method = item_factory_instance.get_method<Il2CppObject*(*)(
                Il2CppObject*, Il2CppString*, Il2CppString*,
                Il2CppObject*)>("CreateItem", 3);


            Il2CppObject* item = create_item_method(item_factory,
                                                    il2cpp::il2cpp_string_new(generate_mongo_id().c_str()),
                                                    il2cpp::il2cpp_string_new(item_id->get().c_str()), nullptr);

            Il2CppObjectInstance inventory_controller(
                main_player.get_field<Il2CppObject*>("_inventoryController"));

            Il2CppObjectInstance inventory(
                inventory_controller.get_method<Il2CppObject*(*)(Il2CppObject*)>("get_Inventory", 0)(
                    inventory_controller.get_instance()));

            Il2CppObjectInstance equipment(
                inventory.get_field<Il2CppObject*>("Equipment"));

            // TODO: make it so it actually goes into the backpack
            // 3 = Knife
            Il2CppObjectInstance backpack_slot(
                equipment.get_method<Il2CppObject*(*)(Il2CppObject*, int)>("GetSlot", 1)(
                    equipment.get_instance(), 3));

            backpack_slot.get_method<Il2CppObject*(*)(Il2CppObject*, Il2CppObject*)>("Add", 1)(
                backpack_slot.get_instance(), item);
        }
    }

    void init() override
    {
        const Il2CppImage* assembly = il2utils::resolve_image("Assembly-CSharp.dll");
        const Il2CppClass* game_world_class = il2utils::resolve_class(assembly, "EFT", "GameWorld");
        il2utils::hook_method(game_world_class, "InitLevel", 6, hk_init_level, &o_init_level);
    }
};
