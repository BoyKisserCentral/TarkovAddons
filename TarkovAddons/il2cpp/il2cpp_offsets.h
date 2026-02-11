#pragma once
#include <windows.h>
#include <Psapi.h>
#include "../util/scan.h"
#include "../util/logger.h"

namespace il2cpp_offsets
{
    inline HMODULE module_base;
    inline DWORD module_size;

    // direct pattern
#define PATTERN(pattern)  reinterpret_cast<PVOID>(scan::find_pattern(pattern, reinterpret_cast<char*>(module_base), module_size))

    // xref pattern for short call (call ?? ?? ?? ??)
#define PATTERN_CALL(pattern) reinterpret_cast<PVOID>(scan::find_pattern_xref(pattern, reinterpret_cast<char*>(module_base), module_size, 1, 5))

    // load from exports
#define IMPORT(name) reinterpret_cast<PVOID>(scan::import(name))

    // worse case scenario, static offset from the exported address to skip the protection
#define IMPORT_OFFSET(name, offset) reinterpret_cast<PVOID>(scan::import(name) + (offset))

    static inline PVOID il2cpp_class_from_name;
    static inline PVOID il2cpp_class_get_nested_types;
    static inline PVOID il2cpp_class_get_field_from_name;
    static inline PVOID il2cpp_class_get_method_from_name;
    static inline PVOID il2cpp_domain_get;
    static inline PVOID il2cpp_domain_get_assemblies;
    static inline PVOID il2cpp_field_static_get_value;
    static inline PVOID il2cpp_field_static_set_value;
    static inline PVOID il2cpp_string_new;
    static inline PVOID il2cpp_type_get_object;

    inline void init()
    {
        logger::info("Loading Il2CPP API");

        module_base = GetModuleHandleA("GameAssembly.dll");
        MODULEINFO info = {};
        GetModuleInformation(GetCurrentProcess(), module_base, &info, sizeof(MODULEINFO));
        module_size = info.SizeOfImage;

        il2cpp_class_from_name = PATTERN_CALL("E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B E8 33 D2");
        il2cpp_class_get_nested_types = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 48 85 D2 0F 84 ? ? ? ? 48 83 79 ? 00 0F 85");
        il2cpp_class_get_field_from_name = PATTERN_CALL("E8 ? ? ? ? 48 63 4B ? ? ? ? ? ? 48 63 40");
        il2cpp_class_get_method_from_name = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 41 8B F1 41 8B F8");
        il2cpp_domain_get = PATTERN_CALL("E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8D 15 ? ? ? ? 48 8B D8");
        il2cpp_domain_get_assemblies = PATTERN("48 8B 05 ? ? ? ? 48 2B 05 ? ? ? ? 48 C1 F8");
        il2cpp_field_static_get_value = PATTERN_CALL(
            "E8 ? ? ? ? 48 8B 44 24 ? EB ? 49 8B C6");
        il2cpp_field_static_set_value = PATTERN_CALL(
            "E8 ? ? ? ? 0F 57 C0 0F 11 44 24 ? 48 C7 44 24 ? ? ? ? ? 48 C7 44 24 ? ? ? ? ? 8B 05");
        il2cpp_string_new = PATTERN("48 C7 C2 ? ? ? ? 48 FF C2 ? ? ? 00 75 ? E9");
        il2cpp_type_get_object = PATTERN_CALL("E8 ? ? ? ? 49 8B CE ? ? ? E8 ? ? ? ? B0 ? EB");

        logger::info("Il2CPP API Loaded");
    }
}
