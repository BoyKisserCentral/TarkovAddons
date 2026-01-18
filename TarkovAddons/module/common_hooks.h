#pragma once
#include "ModuleManager.h"
#include "game_state.h"

namespace common_hooks
{
    static Il2CppImage* assembly_csharp;
    static const Il2CppClass* game_world_class;

    using update_sig = void(*)(Il2CppObject*);
    static update_sig o_tarkov_application_update = nullptr;
    static update_sig o_game_world_update = nullptr;

    static const Il2CppClass* is_in_raid;

    static Il2CppObject* asset_bundle_load_object = nullptr;
    static bool asset_bundle_loaded = false;

    static void hk_tarkov_application_update(Il2CppObject* instance)
    {
        // load asset bundle from game thread
        if (!asset_bundle_load_object)
        {
            logger::info("Loading Asset Bundle");
            asset_bundle_load_object = asset_bundles::start_load();
        }
        else if (!asset_bundle_loaded)
        {
            asset_bundle_loaded = asset_bundles::check_progress(asset_bundle_load_object);
        }

        // set ingame status
        game_state::is_in_raid = il2utils::get_static_field<bool>(is_in_raid, "InRaid");

        ModuleManager::get_instance()->apply([](Module* m)
        {
            m->application_update();
        });

        o_tarkov_application_update(instance);
    }

    static void hk_game_world_update(Il2CppObject* instance)
    {
        ModuleManager::get_instance()->apply([instance](Module* m)
        {
            m->gameworld_update(game_world_class, instance);
        });

        o_game_world_update(instance);
    }

    inline void init()
    {
        // set assembly csharp image
        assembly_csharp = il2utils::resolve_image("Assembly-CSharp.dll");

        // ingame status class
        is_in_raid = il2utils::resolve_class(assembly_csharp, "EFT", "InGameStatus");

        // hook game world update
        game_world_class = il2utils::resolve_class(
            assembly_csharp, "EFT", "GameWorld");
        il2utils::hook_method(game_world_class, "Update", 0, hk_game_world_update,
                              &o_game_world_update);

        // hook tarkov application update
        const Il2CppClass* tarkov_application_class = tarkov_application_class = il2utils::resolve_class(
            assembly_csharp, "EFT", "TarkovApplication");
        il2utils::hook_method(tarkov_application_class, "Update", 0, hk_tarkov_application_update,
                              &o_tarkov_application_update);
    }
}
