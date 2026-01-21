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

static bool no_limit = false;

using check_compat_sig = bool(*)(Il2CppObject*, Il2CppObject*);
static check_compat_sig o_check_compat_stack_slot = nullptr;

inline bool hk_check_compat_stack_slot(Il2CppObject* instance, Il2CppObject* item)
{
    if (no_limit) return true;
    return o_check_compat_stack_slot(instance, item);
}

static check_compat_sig o_check_compat_item_controller = nullptr;

inline bool hk_check_compat_item_controller(Il2CppObject* instance, Il2CppObject* item)
{
    if (no_limit) return true;
    return o_check_compat_item_controller(instance, item);
}

static check_compat_sig o_check_compat_magazine = nullptr;

inline bool hk_check_compat_magazine(Il2CppObject* instance, Il2CppObject* item)
{
    if (no_limit) return true;
    return o_check_compat_magazine(instance, item);
}

static check_compat_sig o_check_compat_virtual_container = nullptr;

inline bool hk_check_compat_virtual_container(Il2CppObject* instance, Il2CppObject* item)
{
    if (no_limit) return true;
    return o_check_compat_virtual_container(instance, item);
}

static check_compat_sig o_check_compat_slot = nullptr;

inline bool hk_check_compat_slot(Il2CppObject* instance, Il2CppObject* item)
{
    if (no_limit) return true;
    return o_check_compat_slot(instance, item);
}

static check_compat_sig o_check_compat_grid = nullptr;

inline bool hk_check_compat_grid(Il2CppObject* instance, Il2CppObject* item)
{
    if (no_limit) return true;
    return o_check_compat_grid(instance, item);
}

using check_restrictions_sig = bool(*)(Il2CppObject*, Il2CppObject*, Il2CppObject*);
static check_restrictions_sig o_check_restrictions = nullptr;

inline bool hk_check_restrictions(Il2CppObject* instance, Il2CppObject* item, Il2CppObject* controller)
{
    if (no_limit) return false;
    return o_check_restrictions(instance, item, controller);
}

static check_restrictions_sig o_check_special_slot = nullptr;

inline bool hk_check_special_slot(Il2CppObject* instance, Il2CppObject* item, Il2CppObject* controller)
{
    if (no_limit) return false;
    return o_check_special_slot(instance, item, controller);
}

static check_restrictions_sig o_check_slot_restrictions = nullptr;

inline bool hk_check_slot_restrictions(Il2CppObject* instance, Il2CppObject* item, Il2CppObject* controller)
{
    if (no_limit) return false;
    return o_check_slot_restrictions(instance, item, controller);
}

static bool big_grid = false;

using get_grid_size_sig = UINT64(*)(Il2CppObject*, Il2CppString*);
static get_grid_size_sig o_get_grid_size;

inline UINT64 hk_get_grid_size(Il2CppObject* instance, Il2CppString* profile_id)
{
    UINT64 res = o_get_grid_size(instance, profile_id);

    if (big_grid)
    {
        // intvec2(0xF, 0xF)
        return 0xF0000000F;
    }

    return res;
}

class ItemModule : Module
{
public:
    ItemModule() : Module("Item", Exploit)
    {
    }

    TextboxValue* item_id = conf(new TextboxValue("", "Item Id"));
    SelectValue* item_slot = conf(new SelectValue(4, {
                                                      "Primary Weapon", "Secondary Weapon", "Holster", "Melee",
                                                      "Backpack", "Secure Container", "Rig", "Armor", "Pockets",
                                                      "Eyewear", "FaceCover", "Headwear", "Earpiece", "Dog-tag",
                                                      "Armband"
                                                  }, "Item Slot"));
    IntSliderValue* amount = conf(new IntSliderValue(1, 1, 100, "Item Amount"));
    CheckboxValue* infinite = conf(new CheckboxValue(false, "Infinite"));
    CheckboxValue* fir = conf(new CheckboxValue(true, "Found in Raid"));
    CheckboxValue* replace_slot = conf(new CheckboxValue(false, "Replace Slot"));

    ActionRowValue* create_item = conf(new ActionRowValue([&]
        {
            create_item_impl();
        }, "Create Item")
    );

    CheckboxValue* no_slot_limits = conf(
        new CheckboxValue(false, "No Slot Limits"));

    CheckboxValue* increased_transfer_size = conf(
        new CheckboxValue(false, "Increased Transfer Size"));

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
        no_limit = no_slot_limits->get_value();
        big_grid = increased_transfer_size->get_value();
    }

    void gameworld_update(const Il2CppClass* game_world_class, Il2CppObjectInstance game_world_instance,
                          Il2CppObjectInstance main_player) override
    {
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

            Il2CppObjectInstance equipment_slot(
                equipment.get_method<Il2CppObject*(*)(Il2CppObject*, int)>("GetSlot", 1)(
                    equipment.get_instance(), item_slot->get_value()));


            if (!replace_slot->get_value())
            {
                Il2CppObject* item_ptr = equipment_slot.get_method<Il2CppObject*(*)(Il2CppObject*)>(
                    "get_ContainedItem", 0)(
                    equipment_slot.get_instance());

                if (item_ptr)
                {
                    Il2CppObjectInstance slot_item_instance(item_ptr);
                    const auto grids = slot_item_instance.get_field<Il2CppArray*>("Grids");
                    for (size_t i = 0; i < grids->max_length; ++i)
                    {
                        Il2CppObjectInstance grid(reinterpret_cast<Il2CppObject**>(&grids->data)[0]);
                        Il2CppObject* space = grid.get_method<Il2CppObject*(
                            *)(Il2CppObject*, Il2CppObject*)>("FindFreeSpace", 1)(grid.get_instance(), item);

                        if (!space) continue;

                        grid.get_method<void(*)(Il2CppObject*, Il2CppObject*, Il2CppObject*)>("PlaceItem", 2)(
                            grid.get_instance(), item, space);

                        break;
                    }
                }
            }
            else
            {
                equipment_slot.get_method<Il2CppObject*(*)(Il2CppObject*, Il2CppObject*)>("Add", 1)(
                    equipment_slot.get_instance(), item);
            }

            Il2CppObjectInstance item_instance(item);

            if (infinite->get_value())
            {
                item_instance.set_field("UnlimitedCount", true);
            }

            item_instance.set_field("StackObjectsCount", amount->get_value());

            if (fir->get_value())
            {
                item_instance.get_method<void(*)(Il2CppObject*, bool)>("set_SpawnedInSession", 1)(item, true);
            }
        }
    }

    void init() override
    {
        const Il2CppImage* assembly = il2utils::resolve_image("Assembly-CSharp.dll");
        const Il2CppClass* game_world_class = il2utils::resolve_class(assembly, "EFT", "GameWorld");
        il2utils::hook_method(game_world_class, "InitLevel", 6, hk_init_level, &o_init_level);

        const Il2CppClass* stack_slot_class = il2utils::resolve_class(assembly, "EFT.InventoryLogic", "StackSlot");
        il2utils::hook_method(stack_slot_class, "CheckCompatibility", 1, hk_check_compat_stack_slot,
                              &o_check_compat_stack_slot);

        const Il2CppClass* item_controller_class = il2utils::resolve_class(
            assembly, "EFT.InventoryLogic", "ItemController");
        il2utils::hook_method(item_controller_class, "CheckCompatibility", 1, hk_check_compat_item_controller,
                              &o_check_compat_item_controller);
        il2utils::hook_method(item_controller_class, "CheckRestrictions", 2, hk_check_restrictions,
                              &o_check_restrictions);
        il2utils::hook_method(item_controller_class, "CheckForOnlySpecialSlotsItem", 2, hk_check_special_slot,
                              &o_check_special_slot);
        il2utils::hook_method(item_controller_class, "CheckSlotRestrictions", 2, hk_check_slot_restrictions,
                              &o_check_slot_restrictions);

        const Il2CppClass* magazine_class = il2utils::resolve_class(assembly, "EFT.InventoryLogic", "Magazine");
        il2utils::hook_method(magazine_class, "CheckCompatibility", 1, hk_check_compat_magazine,
                              &o_check_compat_magazine);

        const Il2CppClass* virtual_container_class = il2utils::resolve_class(
            assembly, "EFT.InventoryLogic", "VirtualContainer");
        il2utils::hook_method(virtual_container_class, "CheckCompatibility", 1, hk_check_compat_virtual_container,
                              &o_check_compat_virtual_container);

        const Il2CppClass* grid_class = il2utils::resolve_class(assembly, "EFT.InventoryLogic", "Grid");
        il2utils::hook_method(grid_class, "CheckCompatibility", 1, hk_check_compat_grid, &o_check_compat_grid);

        const Il2CppClass* slot_class = il2utils::resolve_class(assembly, "EFT.InventoryLogic", "Slot");
        il2utils::hook_method(slot_class, "CheckCompatibility", 1, hk_check_compat_slot, &o_check_compat_slot);

        const Il2CppClass* transfer_items_controller = il2utils::resolve_class(
            assembly, "EFT", "TransferItemsController");
        il2utils::hook_method(transfer_items_controller, "GetGridSizeForProfileId", 1, hk_get_grid_size,
                              &o_get_grid_size);
    }
};
