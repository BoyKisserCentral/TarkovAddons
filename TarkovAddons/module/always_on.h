#pragma once
#include "../il2cpp/Il2CppObjectInstance.h"
#include "../il2cpp/il2utils.h"

namespace always_on
{
    static inline Il2CppImage* assembly_csharp;

    using set_selected_location_sig = void(*)(Il2CppObject*, Il2CppObject*);

    static inline set_selected_location_sig o_set_selected_location = nullptr;

    inline void hk_set_selected_location(Il2CppObject* _this, Il2CppObject* location)
    {
        if (location != nullptr)
        {
            const Il2CppClass* location_class = il2utils::resolve_class_nested(
                il2utils::resolve_class(
                    assembly_csharp, "JsonType", "LocationSettings"), "Location");
            auto location_instance = new Il2CppObjectInstance(location_class, location);
            // force offline raid
            location_instance->set_field("ForceOnlineRaidInPVE", false);
            location_instance->set_field("ForceOfflineRaidInPVE", true);

            // unlock location
            location_instance->set_field("Enabled", true);
            location_instance->set_field("Locked", false);
            location_instance->set_field("LockedByQuest", false);
            location_instance->set_field("RequiredPlayerLevelMin", 0);
            location_instance->set_field("RequiredPlayerLevelMax", INT_MAX);
        }
        o_set_selected_location(_this, location);
    }

    inline void init()
    {
        // set assembly csharp image
        assembly_csharp = il2utils::resolve_image("Assembly-CSharp.dll");

        // always offline raid and location unlock
        const Il2CppClass* match_maker_selection_location_screen = il2utils::resolve_class(
            assembly_csharp, "EFT.UI.Matchmaker", "MatchMakerSelectionLocationScreen");
        il2utils::hook_method(match_maker_selection_location_screen, "set_SelectedLocation", 1,
                              hk_set_selected_location,
                              &o_set_selected_location);
    }
}
