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

    static inline PVOID il2cpp_init;
    static inline PVOID il2cpp_init_utf16;
    static inline PVOID il2cpp_shutdown;
    static inline PVOID il2cpp_set_config_dir;
    static inline PVOID il2cpp_set_data_dir;
    static inline PVOID il2cpp_set_temp_dir;
    static inline PVOID il2cpp_set_commandline_arguments;
    static inline PVOID il2cpp_set_commandline_arguments_utf16;
    static inline PVOID il2cpp_set_config_utf16;
    static inline PVOID il2cpp_set_config;
    static inline PVOID il2cpp_set_memory_callbacks;
    static inline PVOID il2cpp_get_corlib;
    static inline PVOID il2cpp_add_internal_call;
    static inline PVOID il2cpp_resolve_icall;
    static inline PVOID il2cpp_alloc;
    static inline PVOID il2cpp_free;

    // array
    static inline PVOID il2cpp_array_class_get;
    static inline PVOID il2cpp_array_get_byte_length;
    static inline PVOID il2cpp_array_new;
    static inline PVOID il2cpp_array_new_specific;
    static inline PVOID il2cpp_array_new_full;
    static inline PVOID il2cpp_bounded_array_class_get;

    // assembly
    static inline PVOID il2cpp_assembly_get_image;

    // class
    static inline PVOID il2cpp_class_enum_basetype;
    static inline PVOID il2cpp_class_is_assignable_from;
    static inline PVOID il2cpp_class_is_subclass_of;
    static inline PVOID il2cpp_class_has_parent;
    static inline PVOID il2cpp_class_from_il2cpp_type;
    static inline PVOID il2cpp_class_from_name;
    static inline PVOID il2cpp_class_from_system_type;
    static inline PVOID il2cpp_class_get_element_class;
    static inline PVOID il2cpp_class_get_events;
    static inline PVOID il2cpp_class_get_fields;
    static inline PVOID il2cpp_class_get_nested_types;
    static inline PVOID il2cpp_class_get_interfaces;
    static inline PVOID il2cpp_class_get_properties;
    static inline PVOID il2cpp_class_get_property_from_name;
    static inline PVOID il2cpp_class_get_field_from_name;
    static inline PVOID il2cpp_class_get_methods;
    static inline PVOID il2cpp_class_get_method_from_name;
    static inline PVOID il2cpp_class_value_size;
    static inline PVOID il2cpp_class_is_blittable;
    static inline PVOID il2cpp_class_get_flags;
    static inline PVOID il2cpp_class_is_abstract;
    static inline PVOID il2cpp_class_is_interface;
    static inline PVOID il2cpp_class_array_element_size;
    static inline PVOID il2cpp_class_from_type;
    static inline PVOID il2cpp_class_get_type_token;
    static inline PVOID il2cpp_class_has_attribute;
    static inline PVOID il2cpp_class_has_references;
    static inline PVOID il2cpp_class_is_enum;
    static inline PVOID il2cpp_class_get_image;
    static inline PVOID il2cpp_class_get_assemblyname;
    static inline PVOID il2cpp_class_get_rank;

    // bitmap
    static inline PVOID il2cpp_class_get_bitmap_size;
    static inline PVOID il2cpp_class_get_bitmap;

    // stats
    static inline PVOID il2cpp_stats_dump_to_file;
    static inline PVOID il2cpp_stats_get_value;

    // domain
    static inline PVOID il2cpp_domain_get;
    static inline PVOID il2cpp_domain_assembly_open;
    static inline PVOID il2cpp_domain_get_assemblies;

    // exception
    static inline PVOID il2cpp_raise_exception;
    static inline PVOID il2cpp_exception_from_name_msg;
    static inline PVOID il2cpp_get_exception_argument_null;
    static inline PVOID il2cpp_format_exception;
    static inline PVOID il2cpp_format_stack_trace;
    static inline PVOID il2cpp_unhandled_exception;

    // field
    static inline PVOID il2cpp_field_get_offset;
    static inline PVOID il2cpp_field_get_value;
    static inline PVOID il2cpp_field_get_value_object;
    static inline PVOID il2cpp_field_has_attribute;
    static inline PVOID il2cpp_field_set_value;
    static inline PVOID il2cpp_field_static_get_value;
    static inline PVOID il2cpp_field_static_set_value;
    static inline PVOID il2cpp_field_set_value_object;

    // gc
    static inline PVOID il2cpp_gc_collect;
    static inline PVOID il2cpp_gc_collect_a_little;
    static inline PVOID il2cpp_gc_disable;
    static inline PVOID il2cpp_gc_enable;
    static inline PVOID il2cpp_gc_is_disabled;
    static inline PVOID il2cpp_gc_get_used_size;
    static inline PVOID il2cpp_gc_get_heap_size;
    static inline PVOID il2cpp_gc_wbarrier_set_field;

    // gchandle
    static inline PVOID il2cpp_gchandle_new;
    static inline PVOID il2cpp_gchandle_new_weakref;
    static inline PVOID il2cpp_gchandle_get_target;
    static inline PVOID il2cpp_gchandle_free;

    // liveness
    static inline PVOID il2cpp_unity_liveness_calculation_from_root;
    static inline PVOID il2cpp_unity_liveness_calculation_from_statics;

    // method
    static inline PVOID il2cpp_method_get_object;
    static inline PVOID il2cpp_method_is_generic;
    static inline PVOID il2cpp_method_is_inflated;
    static inline PVOID il2cpp_method_is_instance;
    static inline PVOID il2cpp_method_get_param;
    static inline PVOID il2cpp_method_has_attribute;
    static inline PVOID il2cpp_method_get_param_name;

    // property
    static inline PVOID il2cpp_property_get_flags;
    static inline PVOID il2cpp_property_get_parent;

    // object
    static inline PVOID il2cpp_object_get_class;
    static inline PVOID il2cpp_object_get_size;
    static inline PVOID il2cpp_object_get_virtual_method;
    static inline PVOID il2cpp_object_new;
    static inline PVOID il2cpp_value_box;

    // monitor
    static inline PVOID il2cpp_monitor_enter;
    static inline PVOID il2cpp_monitor_try_enter;
    static inline PVOID il2cpp_monitor_exit;
    static inline PVOID il2cpp_monitor_pulse;
    static inline PVOID il2cpp_monitor_pulse_all;
    static inline PVOID il2cpp_monitor_wait;
    static inline PVOID il2cpp_monitor_try_wait;

    // runtime
    static inline PVOID il2cpp_runtime_invoke;
    static inline PVOID il2cpp_runtime_invoke_convert_args;
    static inline PVOID il2cpp_runtime_class_init;
    static inline PVOID il2cpp_runtime_object_init;
    static inline PVOID il2cpp_runtime_object_init_exception;
    static inline PVOID il2cpp_runtime_unhandled_exception_policy_set;

    // string
    static inline PVOID il2cpp_string_new;
    static inline PVOID il2cpp_string_new_len;
    static inline PVOID il2cpp_string_new_utf16;
    static inline PVOID il2cpp_string_new_wrapper;
    static inline PVOID il2cpp_string_intern;
    static inline PVOID il2cpp_string_is_interned;

    // thread
    static inline PVOID il2cpp_thread_current;
    static inline PVOID il2cpp_thread_attach;
    static inline PVOID il2cpp_thread_detach;
    static inline PVOID il2cpp_thread_get_all_attached_threads;
    static inline PVOID il2cpp_is_vm_thread;

    // stacktrace
    static inline PVOID il2cpp_current_thread_walk_frame_stack;
    static inline PVOID il2cpp_thread_walk_frame_stack;
    static inline PVOID il2cpp_current_thread_get_top_frame;
    static inline PVOID il2cpp_thread_get_top_frame;
    static inline PVOID il2cpp_current_thread_get_frame_at;
    static inline PVOID il2cpp_thread_get_frame_at;
    static inline PVOID il2cpp_current_thread_get_stack_depth;
    static inline PVOID il2cpp_thread_get_stack_depth;

    // type
    static inline PVOID il2cpp_type_get_object;
    static inline PVOID il2cpp_type_get_type;
    static inline PVOID il2cpp_type_get_class_or_element_class;
    static inline PVOID il2cpp_type_get_name;
    static inline PVOID il2cpp_type_is_byref;
    static inline PVOID il2cpp_type_get_attrs;
    static inline PVOID il2cpp_type_equals;
    static inline PVOID il2cpp_type_get_assembly_qualified_name;

    // image
    static inline PVOID il2cpp_image_get_name;
    static inline PVOID il2cpp_image_get_filename;
    static inline PVOID il2cpp_image_get_entry_point;
    static inline PVOID il2cpp_image_get_class;

    // memory information
    static inline PVOID il2cpp_capture_memory_snapshot;
    static inline PVOID il2cpp_free_captured_memory_snapshot;
    static inline PVOID il2cpp_set_find_plugin_callback;

    // logging
    static inline PVOID il2cpp_register_log_callback;

    // debugger
    static inline PVOID il2cpp_debugger_set_agent_options;

    // TLS module
    static inline PVOID il2cpp_unity_install_unitytls_interface;

    // custom attributes
    static inline PVOID il2cpp_custom_attrs_from_class;
    static inline PVOID il2cpp_custom_attrs_from_method;
    static inline PVOID il2cpp_custom_attrs_get_attr;
    static inline PVOID il2cpp_custom_attrs_has_attr;
    static inline PVOID il2cpp_custom_attrs_construct;
    static inline PVOID il2cpp_custom_attrs_free;

    inline void init()
    {
        logger::info("Loading Il2CPP API");

        module_base = GetModuleHandleA("GameAssembly.dll");
        MODULEINFO info = {};
        GetModuleInformation(GetCurrentProcess(), module_base, &info, sizeof(MODULEINFO));
        module_size = info.SizeOfImage;

        il2cpp_init = PATTERN("40 53 48 83 EC ? 48 8B D9 48 8D 15 ? ? ? ? 33 C9");
        il2cpp_init_utf16 = PATTERN("40 53 48 83 EC ? 48 8B D1 48 8D 4C 24 ? E8 ? ? ? ? 48 8B D8");
        il2cpp_shutdown = PATTERN("40 53 55 57 48 83 EC ? 48 8D 2D");
        il2cpp_set_config_dir = IMPORT("il2cpp_set_config_dir"); // too short for a proper pattern
        il2cpp_set_data_dir = PATTERN("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B E9 E8");
        il2cpp_set_temp_dir = IMPORT("il2cpp_set_temp_dir"); // too short for a proper pattern
        il2cpp_set_commandline_arguments = PATTERN(
            "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 0F 29 74 24 ? 48 63 DA");
        il2cpp_set_commandline_arguments_utf16 = PATTERN("48 89 4C 24 ? 53 57 48 83 EC ? 48 63 DA");
        il2cpp_set_config_utf16 = PATTERN(
            "48 83 EC ? 48 8B D1 48 8D 4C 24 ? E8 ? ? ? ? 90 48 8D 4C 24 ? E8 ? ? ? ? 90");
        il2cpp_set_config = PATTERN("40 53 48 83 EC ? 48 8B D9 0F 57 C0 0F 11 44 24 ? 0F 57 C9");
        il2cpp_set_memory_callbacks = PATTERN("? ? ? 0F 11 05 ? ? ? ? 0F 10 49");
        il2cpp_get_corlib = IMPORT("il2cpp_get_corlib"); // too short for a proper pattern
        il2cpp_add_internal_call = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 48 89 54 24 ? 55 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC");
        il2cpp_resolve_icall = PATTERN(
            "48 89 5C 24 ? 48 89 4C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 4C 8B E1");
        il2cpp_alloc = IMPORT("il2cpp_alloc"); // too short for a proper pattern
        il2cpp_free = IMPORT("il2cpp_free"); // too short for a proper pattern

        // array
        il2cpp_array_class_get = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 44 8B FA");
        // il2cpp_array_length implemented because pattern didnt work
        il2cpp_array_get_byte_length = PATTERN("48 83 79 ? 00 ? ? ? 75 ? 48 8B 41 ? 41 0F AF 80");
        il2cpp_array_new = PATTERN("40 53 48 83 EC ? 48 8B DA BA");
        il2cpp_array_new_specific = PATTERN("48 89 5C 24 ? 55 48 83 EC ? 48 8B EA 48 8B D9 E8");
        il2cpp_array_new_full = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 55 41 56 48 83 EC ? 4D 8B E8 4C 8B F2");
        il2cpp_bounded_array_class_get = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 44 8B FA");
        // il2cpp_array_element_size implemented because pattern didnt work

        // assembly
        il2cpp_assembly_get_image = IMPORT("mono_property_get_parent"); // for some reason pattern didnt wanna work

        // class
        il2cpp_class_enum_basetype = PATTERN("48 39 49 ? 75 ? 33 C0 C3 48 8B 41 ? 48 83 C0");
        // il2cpp_class_is_generic implemented because pattern didnt work
        // il2cpp_class_is_inflated implemented because pattern didnt work
        il2cpp_class_is_assignable_from = PATTERN("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B F2");
        il2cpp_class_is_subclass_of = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 41 0F B6 D8 48 8B F2 48 8B F9 E8");
        il2cpp_class_has_parent = PATTERN("48 89 5C 24 ? 57 48 83 EC ? 48 8B DA 48 8B F9 E8 ? ? ? ? 48 8B CB");
        il2cpp_class_from_il2cpp_type = PATTERN("40 53 48 83 EC ? 0F BE 41");
        il2cpp_class_from_name = PATTERN(
            "4C 89 44 24 ? 48 89 54 24 ? 53 55 56 57 41 54 41 55 41 56 41 57 48 81 EC");
        il2cpp_class_from_system_type = PATTERN(
            "40 53 48 83 EC ? 48 8B 49 ? B2 ? E8 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8B C3");
        // il2cpp_class_get_element_class implemented because pattern didnt work
        il2cpp_class_get_events = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 48 85 D2 0F 84 ? ? ? ? ? ? ? 00 0F 85 ? ? ? ? 48 83 B9 ? ? ? ? 00 0F 85 ? ? ? ? 66 83 B9 ? ? ? ? 00 0F 84 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 44 24 ? FF 15 ? ? ? ? 48 8B E8 48 8B 0D ? ? ? ? BB ? ? ? ? 48 3B C1 74 ? B9 ? ? ? ? F0 0F C1 0D ? ? ? ? 85 C9 7F ? 48 8B 0D ? ? ? ? FF 15 ? ? ? ? 48 89 2D ? ? ? ? 89 1D ? ? ? ? EB ? FF 05 ? ? ? ? 48 8D 54 24 ? 48 8B CF E8 ? ? ? ? 90 4C 8B 44 24 ? 41 83 78 ? 00 7E ? 41 83 78 ? ? 75 ? 33 C0 49 89 40 ? 41 89 40 ? 41 8B 50 ? 41 3B 50 ? 74 ? ? ? ? 41 3B 40 ? 7E ? 41 8B 58 ? 2B DA ? ? ? 8B C2 F0 41 0F B1 48 ? 74 ? 8B D0 EB ? 85 D2 79 ? F7 DA 3B DA 0F 4C D3 ? ? ? FF 15 ? ? ? ? EB ? 41 FF 48 ? 66 83 BF ? ? ? ? 00 74 ? 48 8B 87 ? ? ? ? ? ? ? 48 8B 87 ? ? ? ? EB ? ? ? ? 48 83 C0 ? 0F B7 89 ? ? ? ? 48 6B D1");
        il2cpp_class_get_fields = PATTERN(
            "48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 48 85 D2 74 ? ? ? ? 00 75 ? E8 ? ? ? ? 66 83 BB ? ? ? ? 00 74 ? 48 8B 83 ? ? ? ? ? ? ? 48 8B 83 ? ? ? ? 48 8B 5C 24");
        il2cpp_class_get_nested_types = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 48 85 D2 0F 84 ? ? ? ? 48 83 79 ? 00 0F 85");
        il2cpp_class_get_interfaces = PATTERN(
            "48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 48 85 D2 74 ? ? ? ? 00 75 ? E8 ? ? ? ? 66 83 BB ? ? ? ? 00 74 ? 48 8B 83 ? ? ? ? ? ? ? 48 8B 83 ? ? ? ? ? ? ? 48 8B 5C 24");
        il2cpp_class_get_properties = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 48 85 D2 0F 84 ? ? ? ? ? ? ? 00 0F 85 ? ? ? ? 48 83 B9 ? ? ? ? 00 0F 85 ? ? ? ? 66 83 B9 ? ? ? ? 00 0F 84 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 44 24 ? FF 15 ? ? ? ? 48 8B E8 48 8B 0D ? ? ? ? BB ? ? ? ? 48 3B C1 74 ? B9 ? ? ? ? F0 0F C1 0D ? ? ? ? 85 C9 7F ? 48 8B 0D ? ? ? ? FF 15 ? ? ? ? 48 89 2D ? ? ? ? 89 1D ? ? ? ? EB ? FF 05 ? ? ? ? 48 8D 54 24 ? 48 8B CF E8 ? ? ? ? 90 4C 8B 44 24 ? 41 83 78 ? 00 7E ? 41 83 78 ? ? 75 ? 33 C0 49 89 40 ? 41 89 40 ? 41 8B 50 ? 41 3B 50 ? 74 ? ? ? ? 41 3B 40 ? 7E ? 41 8B 58 ? 2B DA ? ? ? 8B C2 F0 41 0F B1 48 ? 74 ? 8B D0 EB ? 85 D2 79 ? F7 DA 3B DA 0F 4C D3 ? ? ? FF 15 ? ? ? ? EB ? 41 FF 48 ? 66 83 BF ? ? ? ? 00 74 ? 48 8B 87 ? ? ? ? ? ? ? 48 8B 87 ? ? ? ? EB ? ? ? ? 48 83 C0 ? 0F B7 89 ? ? ? ? ? ? ? ? 48 8B 8F");
        il2cpp_class_get_property_from_name = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 48 8B EA 48 8B F9 48 85 C9");
        il2cpp_class_get_field_from_name = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B EA 48 8B D9 48 85 C9 74");
        il2cpp_class_get_methods = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 48 85 D2 0F 84 ? ? ? ? ? ? ? 00 0F 85 ? ? ? ? 66 83 B9 ? ? ? ? 00");
        il2cpp_class_get_method_from_name = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 41 8B E9 41 8B F8");
        // il2cpp_class_get_name implemented because pattern didnt work
        // il2cpp_class_get_namespace implemented because pattern didnt work
        // il2cpp_class_get_parent implemented because pattern didnt work
        // il2cpp_class_get_declaring_type implemented because pattern didnt work
        // il2cpp_class_instance_size implemented because pattern didnt work
        // il2cpp_class_num_fields implemented because pattern didnt work
        // il2cpp_class_is_valuetype implemented because pattern didnt work
        il2cpp_class_value_size = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 48 89 54 24 ? 55 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 4C 8B EA");
        il2cpp_class_is_blittable = IMPORT("il2cpp_class_is_blittable"); // too short for a proper pattern
        il2cpp_class_get_flags = IMPORT("il2cpp_class_get_flags"); // too short for a proper pattern
        il2cpp_class_is_abstract = IMPORT("il2cpp_class_is_abstract"); // too short for a proper pattern
        il2cpp_class_is_interface = PATTERN("F6 81 ? ? ? ? ? 75 ? 80 79");
        il2cpp_class_array_element_size = PATTERN("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F BE 41 ? 48 8D 59");
        il2cpp_class_from_type = PATTERN("40 53 48 83 EC ? 0F BE 41");
        // PVOID il2cpp_class_get_type implemented because it was protected and too short for a pattern
        il2cpp_class_get_type_token = IMPORT("il2cpp_class_get_type_token"); // too short for a proper pattern
        il2cpp_class_has_attribute = PATTERN("40 53 48 81 EC ? ? ? ? 48 8B DA 44 8B 81");
        il2cpp_class_has_references = PATTERN(
            "40 53 48 83 EC ? F6 81 ? ? ? ? ? 48 8B D9 75 ? E8 ? ? ? ? F6 83 ? ? ? ? ? 74");
        il2cpp_class_is_enum = IMPORT("il2cpp_class_is_enum"); // too short for a proper pattern
        il2cpp_class_get_image = IMPORT("mono_property_get_parent"); // for some reason pattern didnt wanna work
        il2cpp_class_get_assemblyname = IMPORT("il2cpp_class_get_assemblyname"); // too short for a proper pattern
        il2cpp_class_get_rank = IMPORT("il2cpp_class_get_rank"); // too short for a proper pattern

        // bitmap
        il2cpp_class_get_bitmap_size = PATTERN("8B 81 ? ? ? ? 48 C1 E8");
        il2cpp_class_get_bitmap = IMPORT("il2cpp_class_get_bitmap"); // too short for a proper pattern

        // stats
        il2cpp_stats_dump_to_file = PATTERN("40 53 48 81 EC ? ? ? ? 48 8B D9 BA ? ? ? ? 48 8D 4C 24 ? E8");
        il2cpp_stats_get_value = PATTERN(
            "83 F9 ? 77 ? 48 63 C1 48 8D 15 ? ? ? ? 8B 8C 82 ? ? ? ? 48 03 CA FF E1 48 8B 05");

        // domain
        il2cpp_domain_get = IMPORT("mono_get_root_domain"); // inconsistencies with pattern
        il2cpp_domain_assembly_open = IMPORT("il2cpp_domain_assembly_open"); // too short for a proper pattern
        il2cpp_domain_get_assemblies = PATTERN("40 53 48 83 EC ? 48 8B DA E8 ? ? ? ? 48 8B 48");

        // exception
        il2cpp_raise_exception = PATTERN("40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 8B D3");
        il2cpp_exception_from_name_msg = PATTERN(
            "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 48 89 78 ? 41 56 48 83 EC ? 49 8B F8");
        il2cpp_get_exception_argument_null = PATTERN("48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 E8 ? ? ? ? 48 8B C8");
        il2cpp_format_exception = IMPORT("il2cpp_format_exception"); // structure does not allow for a good pattern
        il2cpp_format_stack_trace = IMPORT("il2cpp_format_stack_trace");
        // structure does not allow for a good pattern
        il2cpp_unhandled_exception = PATTERN("48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 E8 ? ? ? ? E8");

        // field
        // il2cpp_field_get_flags implemented because pattern didnt work
        // il2cpp_field_get_name implemented because pattern didnt work
        // il2cpp_field_get_parent implemented because pattern didnt work
        il2cpp_field_get_offset = IMPORT("mono_field_get_offset");
        // too short for a proper pattern and il2cpp variant is protected
        // il2cpp_field_get_type implemented because pattern didnt work
        il2cpp_field_get_value = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 72 ? 49 8B F8");
        il2cpp_field_get_value_object = PATTERN("40 55 56 57 48 83 EC ? 48 8D 6C 24 ? 48 8B F9");
        il2cpp_field_has_attribute = IMPORT("il2cpp_field_has_attribute"); // too short for a proper pattern
        il2cpp_field_set_value = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 72 ? 49 8B D8 48 63 7A");
        il2cpp_field_static_get_value = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 41 ? 49 8B D8 48 8B FA");
        il2cpp_field_static_set_value = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B E9 48 8B FA");
        il2cpp_field_set_value_object = PATTERN("48 63 42 ? 49 8B D0");

        // gc
        il2cpp_gc_collect = PATTERN("48 83 EC ? 33 D2 33 C9");
        il2cpp_gc_collect_a_little = PATTERN("40 53 48 83 EC ? 83 3D ? ? ? ? 00 74 ? 48 8D 0D");
        il2cpp_gc_disable = PATTERN(
            "48 83 EC ? 8B 05 ? ? ? ? 85 C0 74 ? 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 8B 05 ? ? ? ? FF 05");
        il2cpp_gc_enable = PATTERN(
            "48 83 EC ? 8B 05 ? ? ? ? 85 C0 74 ? 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 8B 05 ? ? ? ? FF 0D");
        il2cpp_gc_is_disabled = IMPORT("il2cpp_gc_is_disabled"); // too short for a proper pattern
        il2cpp_gc_get_used_size = PATTERN("40 53 48 83 EC ? E8 ? ? ? ? 48 8B D8 E8");
        il2cpp_gc_get_heap_size = IMPORT("il2cpp_gc_get_heap_size"); // too short for a proper pattern
        il2cpp_gc_wbarrier_set_field = IMPORT("il2cpp_gc_wbarrier_set_field"); // too short for a proper pattern

        // gchandle
        il2cpp_gchandle_new = PATTERN("0F B6 C2 4C 8B C9 45 33 C0");
        il2cpp_gchandle_new_weakref = PATTERN("40 53 48 83 EC ? 44 0F B6 C2 48 8B D1");
        il2cpp_gchandle_get_target = PATTERN("48 89 6C 24 ? 56 57 41 57 48 83 EC ? 8B F9");
        il2cpp_gchandle_free = PATTERN("48 89 74 24 ? 57 48 83 EC ? 8B F9 48 8D 05 ? ? ? ? 83 E1");

        // liveness
        il2cpp_unity_liveness_calculation_from_root = PATTERN("40 53 48 83 EC ? 48 8B 42 ? 48 8B DA ? ? ? 48 85 C0");
        il2cpp_unity_liveness_calculation_from_statics = PATTERN("40 57 41 54 41 57 48 83 EC ? 48 8B F9");

        // method
        // il2cpp_method_get_return_type implemented because it was protected and too short for a pattern
        // il2cpp_method_get_declaring_type implemented because pattern didnt work
        // il2cpp_method_get_name implemented because pattern didnt work
        // il2cpp_method_get_from_reflection implemented because pattern didnt work
        il2cpp_method_get_object = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 48 8B EA 48 8B F1 48 85 D2");
        il2cpp_method_is_generic = IMPORT("mono_method_is_generic");
        // too short for a proper pattern and il2cpp variant is protected
        il2cpp_method_is_inflated = IMPORT("mono_method_is_inflated");
        // too short for a proper pattern and il2cpp variant is protected
        il2cpp_method_is_instance = PATTERN("0F B6 41 ? C0 E8 ? F6 D0");
        // il2cpp_method_get_param_count implemented because pattern didnt work
        il2cpp_method_get_param = PATTERN("0F B6 41 ? 3B D0 73");
        // il2cpp_method_get_class implemented because pattern didnt work
        il2cpp_method_has_attribute = IMPORT_OFFSET("il2cpp_method_has_attribute", 65);
        // protected, too short for a proper pattern and has no callers
        // il2cpp_method_get_flags implemented because pattern didnt work
        // this is potentially a bad pattern, inline pattern
        // il2cpp_method_get_token implemented because pattern didnt work
        il2cpp_method_get_param_name = PATTERN("40 53 48 83 EC ? 0F B6 41 ? 8B DA 3B D0 73");

        // property
        il2cpp_property_get_flags = IMPORT("il2cpp_property_get_flags"); // too short for a proper pattern
        // il2cpp_property_get_get_method implemented because pattern didnt work
        // il2cpp_property_get_set_method implemented because pattern didnt work
        // il2cpp_property_get_name implemented because pattern didnt work
        il2cpp_property_get_parent = IMPORT("mono_property_get_parent"); // for some reason pattern didnt wanna work

        // object
        il2cpp_object_get_class = IMPORT("mono_property_get_parent"); // for some reason pattern didnt wanna work
        il2cpp_object_get_size = IMPORT("mono_property_get_parent"); // for some reason pattern didnt wanna work
        il2cpp_object_get_virtual_method = PATTERN("40 53 48 83 EC ? F6 42 ? ? 48 8B DA 4C 8B D9");
        il2cpp_object_new = PATTERN("48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 83 7B ? 00");
        // il2cpp_object_unbox implemented because pattern didnt work
        il2cpp_value_box = PATTERN("48 89 5C 24 ? 56 48 83 EC ? 83 79 ? 00 48 8B F2 48 8B D9 7C");

        // monitor
        il2cpp_monitor_enter = PATTERN("40 53 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 8B F2");
        il2cpp_monitor_try_enter = PATTERN("40 53 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 8B F2");
        il2cpp_monitor_exit = PATTERN("48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 E8 ? ? ? ? 48 8B D8");
        il2cpp_monitor_pulse = PATTERN("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? E8");
        il2cpp_monitor_pulse_all = PATTERN("48 89 5C 24 ? 57 48 83 EC ? E8 ? ? ? ? 48 8B D8");
        il2cpp_monitor_wait = IMPORT("il2cpp_monitor_wait"); // too short for a proper pattern
        il2cpp_monitor_try_wait = PATTERN("89 54 24 ? 48 89 4C 24 ? 53 57 41 54 41 55 41 56");

        // runtime
        il2cpp_runtime_invoke = PATTERN("48 89 5C 24 ? 48 89 74 24 ? 4C 89 4C 24 ? 57 48 83 EC ? 49 8B F8");
        il2cpp_runtime_invoke_convert_args = PATTERN(
            "44 89 4C 24 ? 4C 89 44 24 ? 48 89 54 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 83 EC");
        il2cpp_runtime_class_init = PATTERN("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 83 B9 ? ? ? ? 00");
        il2cpp_runtime_object_init = PATTERN("48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 48 8D 15");
        il2cpp_runtime_object_init_exception = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B D9 ? ? ? 48 8D 15");
        il2cpp_runtime_unhandled_exception_policy_set = IMPORT("il2cpp_runtime_unhandled_exception_policy_set");

        // string
        // il2cpp_string_length implemented because pattern didnt work
        // il2cpp_string_chars implemented because pattern didnt work
        il2cpp_string_new = PATTERN("40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 44 8B C0");
        il2cpp_string_new_len = PATTERN(
            "40 53 48 83 EC ? 44 8B C2 48 8B D1 48 8D 4C 24 ? E8 ? ? ? ? 90 48 8D 4C 24 ? 48 83 7C 24 ? ? 48 0F 47 4C 24 ? 8B 54 24");
        il2cpp_string_new_utf16 = PATTERN("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 63 DA 48 8B F1 85 D2");
        il2cpp_string_new_wrapper = PATTERN("40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 44 8B C0");
        il2cpp_string_intern = PATTERN("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F1 48 8B 3D");
        il2cpp_string_is_interned = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B E9 48 8B 35");

        // thread
        il2cpp_thread_current = IMPORT("il2cpp_thread_current"); // too short for a proper pattern
        il2cpp_thread_attach = PATTERN("40 56 48 83 EC ? 48 8B F1 48 8B 0D");
        il2cpp_thread_detach = PATTERN("48 83 EC ? 33 D2 E8 ? ? ? ? 48 83 C4 ? E9");
        il2cpp_thread_get_all_attached_threads = PATTERN("48 8B 05 ? ? ? ? 48 8B 50 ? ? ? ? 48 C1 FA");
        il2cpp_is_vm_thread = IMPORT("il2cpp_is_vm_thread"); // too short for a proper pattern

        // stacktrace
        il2cpp_current_thread_walk_frame_stack = PATTERN(
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B E9 48 8B F2 48 8B 0D");
        il2cpp_thread_walk_frame_stack = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F0 48 8B DA 48 8B F9 45 33 C0");
        il2cpp_current_thread_get_top_frame = PATTERN("40 53 48 83 EC ? 48 8B DA 89 4C 24");
        il2cpp_thread_get_top_frame = PATTERN(
            "48 89 5C 24 ? 57 48 83 EC ? 48 8B DA 48 8B F9 45 33 C0 33 D2 48 8D 4C 24");
        il2cpp_current_thread_get_frame_at = PATTERN("40 53 48 83 EC ? 48 8B DA 89 4C 24");
        il2cpp_thread_get_frame_at = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F0 8B DA 48 8B F9 45 33 C0");
        il2cpp_current_thread_get_stack_depth = PATTERN("48 83 EC ? E8 ? ? ? ? 48 8B 48 ? ? ? ? 48 C1 F9");
        il2cpp_thread_get_stack_depth = PATTERN("40 53 48 83 EC ? 48 8B D9 45 33 C0 33 D2");

        // type
        il2cpp_type_get_object = PATTERN("48 89 4C 24 ? 53 48 83 EC ? 48 8B D9 48 C7 44 24 ? 00 00 00 00 48 8B 0D");
        il2cpp_type_get_type = IMPORT("il2cpp_type_get_type"); // too short for a proper pattern
        il2cpp_type_get_class_or_element_class = PATTERN("80 79 ? ? 75 ? ? ? ? B2 ? ? ? ? E9");
        il2cpp_type_get_name = PATTERN("40 53 48 83 EC ? 45 33 C0 48 8B D1");
        il2cpp_type_is_byref = IMPORT("il2cpp_type_is_byref"); // too short for a proper pattern
        il2cpp_type_get_attrs = IMPORT("il2cpp_type_get_attrs"); // too short for a proper pattern
        il2cpp_type_equals = PATTERN("48 83 EC ? 4C 8B C1 48 89 5C 24");
        il2cpp_type_get_assembly_qualified_name = IMPORT("il2cpp_type_get_assembly_qualified_name");
        // structure does not allow for a good pattern

        // image
        // il2cpp_image_get_assembly implemented because pattern didnt work
        il2cpp_image_get_name = IMPORT("mono_property_get_parent"); // for some reason pattern didnt wanna work
        il2cpp_image_get_filename = IMPORT("mono_property_get_parent"); // for some reason pattern didnt wanna work
        il2cpp_image_get_entry_point = PATTERN("4C 8B 41 ? 4D 85 C0 74 ? 41 83 78 ? ? 74");
        // il2cpp_image_get_class_count implemented because pattern didnt work
        il2cpp_image_get_class = IMPORT("il2cpp_image_get_class"); // too short for a proper pattern

        // memory information
        il2cpp_capture_memory_snapshot = PATTERN("48 89 5C 24 ? 57 48 83 EC ? BA");
        il2cpp_free_captured_memory_snapshot = PATTERN(
            "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 33 FF 48 8B D9 8B F7");
        il2cpp_set_find_plugin_callback = IMPORT("il2cpp_set_find_plugin_callback"); // too short for a proper pattern

        // logging
        il2cpp_register_log_callback = IMPORT("il2cpp_register_log_callback"); // too short for a proper pattern

        // debugger
        il2cpp_debugger_set_agent_options = IMPORT("il2cpp_debugger_set_agent_options");
        // too short for a proper pattern, also seems to be empty
        // il2cpp_is_debugger_attached implemented because pattern didnt work

        // TLS module
        il2cpp_unity_install_unitytls_interface = IMPORT("il2cpp_unity_install_unitytls_interface");
        // too short for a proper pattern

        // custom attributes
        il2cpp_custom_attrs_from_class = IMPORT("il2cpp_custom_attrs_from_class"); // too short for a proper pattern
        il2cpp_custom_attrs_from_method = IMPORT("il2cpp_custom_attrs_from_method"); // too short for a proper pattern
        il2cpp_custom_attrs_get_attr = PATTERN("48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B DA 48 8B D1");
        il2cpp_custom_attrs_has_attr = PATTERN("40 53 48 81 EC ? ? ? ? 48 8B DA 48 8B D1");
        il2cpp_custom_attrs_construct = PATTERN("48 83 EC ? 48 8B D1 48 8D 4C 24 ? E8 ? ? ? ? 33 D2");
        il2cpp_custom_attrs_free = IMPORT("il2cpp_custom_attrs_free");
        // too short for a proper pattern, also seems to be empty

        logger::info("Il2CPP API Loaded");
    }
}
