#pragma once
#include <windows.h>
#include <Psapi.h>
#include "../util/scan.h"
#include "../util/logger.h"

namespace il2cpp_offsets
{
    static inline HMODULE module_base;
    static inline DWORD module_size;

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

        il2cpp_class_from_name = PATTERN_CALL("E8 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 15");
        il2cpp_class_get_nested_types = PATTERN_CALL("E8 ? ? ? ? 48 8B F8 48 85 C0 74 ? 4C 8B 47");
        il2cpp_class_get_field_from_name = PATTERN_CALL("E8 ? ? ? ? 48 8B D8 48 85 C0 0F 84 ? ? ? ? E8");
        il2cpp_class_get_method_from_name = PATTERN_CALL("E8 ? ? ? ? 48 89 74 24 ? 48 8D 4C 24 ? 48 89 4C 24 ? 4C 8D 4C 24 ? 4C 8B C7");
        il2cpp_domain_get = PATTERN_CALL("E8 ? ? ? ? 48 8B F0 48 8B C8 E8 ? ? ? ? 48 8B C8");
        il2cpp_domain_get_assemblies = PATTERN("40 53 48 83 EC ? 48 8B DA E8 ? ? ? ? 48 8B 48");
        il2cpp_field_static_get_value = PATTERN_CALL("E8 ? ? ? ? 48 8B 5C 24 ? 48 85 DB 74 ? ? ? ? 75 ? ? ? ? 48 83 E0 ? 0F B6 B0");
        il2cpp_field_static_set_value = PATTERN_CALL("E8 ? ? ? ? C6 05 ? ? ? ? ? 0F 57 C0 0F 11 44 24 ? 66 0F 6F 0D");
        il2cpp_string_new = PATTERN_CALL("E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 48 8D 50 ? 41 83 FE");
        il2cpp_type_get_object = PATTERN_CALL("E8 ? ? ? ? 48 8D 4D ? 48 89 44 2F");

        logger::info("Il2CPP API Loaded");
    }
}
