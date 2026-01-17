#pragma once
#include "il2cpp_offsets.h"
#include "libil2cpp/il2cpp-class-internals.h"
#include "libil2cpp/il2cpp-api-types.h"

namespace il2cpp
{
    inline void il2cpp_init(const char* domain_name)
    {
        return reinterpret_cast<void(*)(const char*)>(il2cpp_offsets::il2cpp_init)(domain_name);
    }

    inline void il2cpp_init_utf16(const Il2CppChar* domain_name)
    {
        return reinterpret_cast<void(*)(const Il2CppChar*)>(il2cpp_offsets::il2cpp_init_utf16)(domain_name);
    }

    inline void il2cpp_shutdown()
    {
        return reinterpret_cast<void(*)()>(il2cpp_offsets::il2cpp_init_utf16)();
    }

    inline void il2cpp_set_config_dir(const char* config_path)
    {
        return reinterpret_cast<void(*)(const char*)>(il2cpp_offsets::il2cpp_set_config_dir)(config_path);
    }

    inline void il2cpp_set_data_dir(const char* data_path)
    {
        return reinterpret_cast<void(*)(const char*)>(il2cpp_offsets::il2cpp_set_data_dir)(data_path);
    }

    inline void il2cpp_set_temp_dir(const char* temp_path)
    {
        return reinterpret_cast<void(*)(const char*)>(il2cpp_offsets::il2cpp_set_temp_dir)(temp_path);
    }

    inline void il2cpp_set_commandline_arguments(
        int argc, const char* const argv[], const char* basedir)
    {
        return reinterpret_cast<void(*)(int, const char* const[], const char*)>(
            il2cpp_offsets::il2cpp_set_commandline_arguments)(
            argc, argv, basedir);
    }

    inline void
    il2cpp_set_commandline_arguments_utf16(int argc, const Il2CppChar* const argv[], const char* basedir)
    {
        return reinterpret_cast<void(*)(int, const Il2CppChar* const[], const char*)>(
            il2cpp_offsets::il2cpp_set_commandline_arguments_utf16)(argc, argv, basedir);
    }

    inline void il2cpp_set_config_utf16(const Il2CppChar* executablePath)
    {
        return reinterpret_cast<void(*)(const Il2CppChar*)>(il2cpp_offsets::il2cpp_set_config_utf16)(executablePath);
    }

    inline void il2cpp_set_config(const char* executablePath)
    {
        return reinterpret_cast<void(*)(const char*)>(il2cpp_offsets::il2cpp_set_config)(executablePath);
    }

    inline void il2cpp_set_memory_callbacks(Il2CppMemoryCallbacks* callbacks)
    {
        return reinterpret_cast<void(*)(Il2CppMemoryCallbacks*)>(
            il2cpp_offsets::il2cpp_set_memory_callbacks)(callbacks);
    }

    inline const Il2CppImage* il2cpp_get_corlib()
    {
        return reinterpret_cast<Il2CppImage*(*)()>(il2cpp_offsets::il2cpp_get_corlib)();
    }

    inline void il2cpp_add_internal_call(
        const char* name, Il2CppMethodPointer method)
    {
        return reinterpret_cast<void(*)(const char*, Il2CppMethodPointer)>(
            il2cpp_offsets::il2cpp_add_internal_call)(name, method);
    }

    inline Il2CppMethodPointer il2cpp_resolve_icall(const char* name)
    {
        return reinterpret_cast<Il2CppMethodPointer(*)(const char*)>(il2cpp_offsets::il2cpp_resolve_icall)(name);
    }

    inline void* il2cpp_alloc(size_t size)
    {
        return reinterpret_cast<void*(*)(size_t)>(il2cpp_offsets::il2cpp_alloc)(size);
    }

    inline void il2cpp_free(void* ptr)
    {
        return reinterpret_cast<void(*)(void*)>(il2cpp_offsets::il2cpp_free)(ptr);
    }

    inline Il2CppClass* il2cpp_array_class_get(
        Il2CppClass* element_class, uint32_t rank)
    {
        return reinterpret_cast<Il2CppClass*(*)(Il2CppClass*, uint32_t, PVOID)>(il2cpp_offsets::il2cpp_array_class_get)(
            element_class, rank, nullptr);
    }

    inline uint32_t il2cpp_array_length(Il2CppArray* array)
    {
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<UINT64>(array) + 24); // NOLINT(performance-no-int-to-ptr)
    }

    inline uint32_t il2cpp_array_get_byte_length(Il2CppArray* array)
    {
        return reinterpret_cast<uint32_t(*)(Il2CppArray*)>(il2cpp_offsets::il2cpp_array_get_byte_length)(array);
    }

    inline Il2CppArray* il2cpp_array_new(
        Il2CppClass* elementTypeInfo, il2cpp_array_size_t length)
    {
        return reinterpret_cast<Il2CppArray*(*)(Il2CppClass*, il2cpp_array_size_t)>(il2cpp_offsets::il2cpp_array_new)(
            elementTypeInfo, length);
    }

    inline Il2CppArray* il2cpp_array_new_specific(
        Il2CppClass* arrayTypeInfo, il2cpp_array_size_t length)
    {
        return reinterpret_cast<Il2CppArray*(*)(Il2CppClass*, il2cpp_array_size_t)>(
            il2cpp_offsets::il2cpp_array_new_specific)(
            arrayTypeInfo, length);
    }

    inline Il2CppArray*
    il2cpp_array_new_full(Il2CppClass* array_class, il2cpp_array_size_t* lengths,
                          il2cpp_array_size_t* lower_bounds)
    {
        return reinterpret_cast<Il2CppArray*(*)(Il2CppClass*, il2cpp_array_size_t*, il2cpp_array_size_t*)>(
            il2cpp_offsets::il2cpp_array_new_full)(array_class, lengths, lower_bounds);
    }

    inline Il2CppClass* il2cpp_bounded_array_class_get(
        Il2CppClass* element_class, uint32_t rank, bool bounded)
    {
        return reinterpret_cast<Il2CppClass*(*)(Il2CppClass*, uint32_t, bool)>(
            il2cpp_offsets::il2cpp_bounded_array_class_get)(
            element_class, rank, bounded);
    }

    inline int il2cpp_array_element_size(const Il2CppClass* array_class)
    {
        return *reinterpret_cast<unsigned int*>(reinterpret_cast<UINT64>(array_class) + 260); // NOLINT(performance-no-int-to-ptr)
    }

    inline const Il2CppImage* il2cpp_assembly_get_image(
        const Il2CppAssembly* assembly)
    {
        return reinterpret_cast<const Il2CppImage*(*)(const Il2CppAssembly*)>(
            il2cpp_offsets::il2cpp_assembly_get_image)(assembly);
    }

    inline const Il2CppType* il2cpp_class_enum_basetype(Il2CppClass* klass)
    {
        return reinterpret_cast<const Il2CppType*(*)(Il2CppClass*)>(il2cpp_offsets::il2cpp_class_enum_basetype)(klass);
    }

    inline bool il2cpp_class_is_generic(const Il2CppClass* klass)
    {
        return (*reinterpret_cast<byte*>(reinterpret_cast<UINT64>(klass) + 309) & 0x10) != 0; // NOLINT(performance-no-int-to-ptr)
    }

    inline bool il2cpp_class_is_inflated(const Il2CppClass* klass)
    {
        return *reinterpret_cast<UINT64*>(reinterpret_cast<UINT64>(klass) + 96) != 0LL; // NOLINT(performance-no-int-to-ptr)
    }

    inline bool il2cpp_class_is_assignable_from(
        Il2CppClass* klass, Il2CppClass* oklass)
    {
        return reinterpret_cast<bool(*)(Il2CppClass*, Il2CppClass*)>(
            il2cpp_offsets::il2cpp_class_is_assignable_from)(klass, oklass);
    }

    inline bool il2cpp_class_is_subclass_of(
        Il2CppClass* klass, Il2CppClass* klassc, bool check_interfaces)
    {
        return reinterpret_cast<Il2CppClass*(*)(Il2CppClass*, Il2CppClass*, bool)>(
            il2cpp_offsets::il2cpp_class_is_subclass_of)(
            klass, klassc, check_interfaces);
    }

    inline bool il2cpp_class_has_parent(
        Il2CppClass* klass, Il2CppClass* klassc)
    {
        return reinterpret_cast<bool(*)(Il2CppClass*, Il2CppClass*)>(
            il2cpp_offsets::il2cpp_class_has_parent)(klass, klassc);
    }

    inline Il2CppClass* il2cpp_class_from_il2cpp_type(const Il2CppType* type)
    {
        return reinterpret_cast<Il2CppClass*(*)(const Il2CppType*)>(
            il2cpp_offsets::il2cpp_class_from_il2cpp_type)(type);
    }

    inline Il2CppClass* il2cpp_class_from_name(
        const Il2CppImage* image, const char* namespaze, const char* name)
    {
        return reinterpret_cast<Il2CppClass*(*)(const Il2CppImage*, const char*, const char*)>(
            il2cpp_offsets::il2cpp_class_from_name)(image, namespaze, name);
    }

    inline Il2CppClass* il2cpp_class_from_system_type(
        Il2CppReflectionType* type)
    {
        return reinterpret_cast<Il2CppClass*(*)(Il2CppReflectionType*)>(
            il2cpp_offsets::il2cpp_class_from_system_type)(type);
    }

    inline Il2CppClass* il2cpp_class_get_element_class(Il2CppClass* klass)
    {
        return *reinterpret_cast<Il2CppClass**>(reinterpret_cast<UINT64>(klass) + 64); // NOLINT(performance-no-int-to-ptr)
    }

    inline const EventInfo* il2cpp_class_get_events(
        Il2CppClass* klass, void* * iter)
    {
        return reinterpret_cast<EventInfo*(*)(Il2CppClass*, void* *)>(il2cpp_offsets::il2cpp_class_get_events)(
            klass, iter);
    }

    inline FieldInfo* il2cpp_class_get_fields(
        Il2CppClass* klass, void* * iter)
    {
        return reinterpret_cast<FieldInfo*(*)(Il2CppClass*, void* *)>(il2cpp_offsets::il2cpp_class_get_fields)(
            klass, iter);
    }

    inline Il2CppClass* il2cpp_class_get_nested_types(
        Il2CppClass* klass, void* * iter)
    {
        return reinterpret_cast<Il2CppClass*(*)(Il2CppClass*, void* *)>(
            il2cpp_offsets::il2cpp_class_get_nested_types)(klass, iter);
    }

    inline Il2CppClass* il2cpp_class_get_interfaces(
        Il2CppClass* klass, void* * iter)
    {
        return reinterpret_cast<Il2CppClass*(*)(Il2CppClass*, void* *)>(
            il2cpp_offsets::il2cpp_class_get_interfaces)(klass, iter);
    }

    inline const PropertyInfo* il2cpp_class_get_properties(
        Il2CppClass* klass, void* * iter)
    {
        return reinterpret_cast<PropertyInfo*(*)(Il2CppClass*, void* *)>(
            il2cpp_offsets::il2cpp_class_get_properties)(klass, iter);
    }

    inline const PropertyInfo* il2cpp_class_get_property_from_name(
        Il2CppClass* klass, const char* name)
    {
        return reinterpret_cast<PropertyInfo*(*)(Il2CppClass*, const char*)>(
            il2cpp_offsets::il2cpp_class_get_property_from_name)(klass, name);
    }

    inline FieldInfo* il2cpp_class_get_field_from_name(
        Il2CppClass* klass, const char* name)
    {
        return reinterpret_cast<FieldInfo*(*)(Il2CppClass*, const char*)>(
            il2cpp_offsets::il2cpp_class_get_field_from_name)(klass, name);
    }

    inline const MethodInfo* il2cpp_class_get_methods(
        Il2CppClass* klass, void* * iter)
    {
        return reinterpret_cast<MethodInfo*(*)(Il2CppClass*, void* *)>(
            il2cpp_offsets::il2cpp_class_get_methods)(klass, iter);
    }

    inline const MethodInfo*
    il2cpp_class_get_method_from_name(Il2CppClass* klass, const char* name, int argsCount)
    {
        return reinterpret_cast<MethodInfo*(*)(Il2CppClass*, const char*, int, PVOID)>(
            il2cpp_offsets::il2cpp_class_get_method_from_name)(
            klass, name, argsCount, nullptr);
    }

    inline const char* il2cpp_class_get_name(Il2CppClass* klass)
    {
        return *reinterpret_cast<const char**>(reinterpret_cast<UINT64>(klass) + 16); // NOLINT(performance-no-int-to-ptr)
    }

    inline const char* il2cpp_class_get_namespace(Il2CppClass* klass)
    {
        return *reinterpret_cast<const char**>(reinterpret_cast<UINT64>(klass) + 24); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppClass* il2cpp_class_get_parent(Il2CppClass* klass)
    {
        return *reinterpret_cast<Il2CppClass**>(reinterpret_cast<UINT64>(klass) + 88); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppClass* il2cpp_class_get_declaring_type(Il2CppClass* klass)
    {
        return *reinterpret_cast<Il2CppClass**>(reinterpret_cast<UINT64>(klass) + 80); // NOLINT(performance-no-int-to-ptr)
    }

    inline int32_t il2cpp_class_instance_size(Il2CppClass* klass)
    {
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<UINT64>(klass) + 248); // NOLINT(performance-no-int-to-ptr)
    }

    inline size_t il2cpp_class_num_fields(const Il2CppClass* enumKlass)
    {
        return *reinterpret_cast<uint16_t*>(reinterpret_cast<UINT64>(enumKlass) + 292); // NOLINT(performance-no-int-to-ptr)
    }

    inline bool il2cpp_class_is_valuetype(const Il2CppClass* klass)
    {
        return *reinterpret_cast<DWORD*>(reinterpret_cast<UINT64>(klass) + 40) >> 31; // NOLINT(performance-no-int-to-ptr)
    }

    inline int32_t il2cpp_class_value_size(
        Il2CppClass* klass, uint32_t* align)
    {
        return reinterpret_cast<int32_t(*)(Il2CppClass*, uint32_t*)>(il2cpp_offsets::il2cpp_class_value_size)(
            klass, align);
    }

    inline bool il2cpp_class_is_blittable(const Il2CppClass* klass)
    {
        return reinterpret_cast<bool(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_is_blittable)(klass);
    }

    inline int il2cpp_class_get_flags(const Il2CppClass* klass)
    {
        return reinterpret_cast<int(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_get_flags)(klass);
    }

    inline bool il2cpp_class_is_abstract(const Il2CppClass* klass)
    {
        return reinterpret_cast<bool(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_is_abstract)(klass);
    }

    inline bool il2cpp_class_is_interface(const Il2CppClass* klass)
    {
        return reinterpret_cast<bool(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_is_interface)(klass);
    }

    inline int il2cpp_class_array_element_size(const Il2CppClass* klass)
    {
        return reinterpret_cast<int(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_array_element_size)(klass);
    }

    inline Il2CppClass* il2cpp_class_from_type(const Il2CppType* type)
    {
        return reinterpret_cast<Il2CppClass*(*)(const Il2CppType*)>(il2cpp_offsets::il2cpp_class_from_type)(type);
    }

    inline const Il2CppType* il2cpp_class_get_type(Il2CppClass* klass)
    {
        return reinterpret_cast<Il2CppType*>(reinterpret_cast<UINT64>(klass) + 32); // NOLINT(performance-no-int-to-ptr)
    }

    inline uint32_t il2cpp_class_get_type_token(Il2CppClass* klass)
    {
        return reinterpret_cast<uint32_t(*)(Il2CppClass*)>(il2cpp_offsets::il2cpp_class_get_type_token)(klass);
    }

    inline bool il2cpp_class_has_attribute(
        Il2CppClass* klass, Il2CppClass* attr_class)
    {
        return reinterpret_cast<bool(*)(Il2CppClass*, Il2CppClass*)>(
            il2cpp_offsets::il2cpp_class_has_attribute)(klass, attr_class);
    }

    inline bool il2cpp_class_has_references(Il2CppClass* klass)
    {
        return reinterpret_cast<bool(*)(Il2CppClass*)>(il2cpp_offsets::il2cpp_class_has_references)(klass);
    }

    inline bool il2cpp_class_is_enum(const Il2CppClass* klass)
    {
        return reinterpret_cast<bool(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_is_enum)(klass);
    }

    inline const Il2CppImage* il2cpp_class_get_image(Il2CppClass* klass)
    {
        return reinterpret_cast<Il2CppImage*(*)(Il2CppClass*)>(il2cpp_offsets::il2cpp_class_get_image)(klass);
    }

    inline const char* il2cpp_class_get_assemblyname(const Il2CppClass* klass)
    {
        return reinterpret_cast<const char*(*)(const Il2CppClass*)>(
            il2cpp_offsets::il2cpp_class_get_assemblyname)(klass);
    }

    inline int il2cpp_class_get_rank(const Il2CppClass* klass)
    {
        return reinterpret_cast<int(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_get_rank)(klass);
    }

    inline size_t il2cpp_class_get_bitmap_size(const Il2CppClass* klass)
    {
        return reinterpret_cast<size_t(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_class_get_bitmap_size)(klass);
    }

    inline void il2cpp_class_get_bitmap(Il2CppClass* klass, size_t* bitmap)
    {
        return reinterpret_cast<void(*)(Il2CppClass*, size_t*)>(
            il2cpp_offsets::il2cpp_class_get_bitmap_size)(klass, bitmap);
    }

    inline bool il2cpp_stats_dump_to_file(const char* path)
    {
        return reinterpret_cast<bool(*)(const char*)>(il2cpp_offsets::il2cpp_stats_dump_to_file)(path);
    }

    inline uint64_t il2cpp_stats_get_value(Il2CppStat stat)
    {
        return reinterpret_cast<uint64_t(*)(Il2CppStat)>(il2cpp_offsets::il2cpp_stats_get_value)(stat);
    }

    inline Il2CppDomain* il2cpp_domain_get()
    {
        return reinterpret_cast<Il2CppDomain*(*)()>(il2cpp_offsets::il2cpp_domain_get)();
    }

    inline const Il2CppAssembly* il2cpp_domain_assembly_open(
        Il2CppDomain* domain, const char* name)
    {
        return reinterpret_cast<Il2CppAssembly*(*)(Il2CppDomain*, const char*)>(
            il2cpp_offsets::il2cpp_domain_assembly_open)(domain, name);
    }

    inline const Il2CppAssembly** il2cpp_domain_get_assemblies(
        const Il2CppDomain* domain, size_t* size)
    {
        return reinterpret_cast<const Il2CppAssembly**(*)(const Il2CppDomain*, size_t*)>(
            il2cpp_offsets::il2cpp_domain_get_assemblies)(domain, size);
    }

    inline void il2cpp_raise_exception(Il2CppException* e)
    {
        return reinterpret_cast<void(*)(Il2CppException*, PVOID)>(il2cpp_offsets::il2cpp_raise_exception)(e, nullptr);
    }

    inline Il2CppException*
    il2cpp_exception_from_name_msg(const Il2CppImage* image, const char* name_space, const char* name, const char* msg)
    {
        return reinterpret_cast<Il2CppException*(*)(const Il2CppImage*, const char*, const char*, const char*)>(
            il2cpp_offsets::il2cpp_exception_from_name_msg)(image, name_space, name, msg);
    }

    inline Il2CppException* il2cpp_get_exception_argument_null(
        const char* arg)
    {
        return reinterpret_cast<Il2CppException*(*)(const char*)>(
            il2cpp_offsets::il2cpp_get_exception_argument_null)(arg);
    }

    inline void il2cpp_format_exception(
        const Il2CppException* ex, char* message, int message_size)
    {
        return reinterpret_cast<void(*)(const Il2CppException*, char*, int)>(il2cpp_offsets::il2cpp_format_exception)(
            ex, message, message_size);
    }

    inline void il2cpp_format_stack_trace(
        const Il2CppException* ex, char* output, int output_size)
    {
        return reinterpret_cast<void(*)(const Il2CppException*, char*, int)>(il2cpp_offsets::il2cpp_format_stack_trace)(
            ex, output, output_size);
    }

    inline void il2cpp_unhandled_exception(Il2CppException* e)
    {
        return reinterpret_cast<void(*)(Il2CppException*)>(il2cpp_offsets::il2cpp_format_stack_trace)(e);
    }

    inline int il2cpp_field_get_flags(FieldInfo* field)
    {
        return *reinterpret_cast<uint16_t*>(*reinterpret_cast<UINT64*>(reinterpret_cast<UINT64>(field) + 8) + 8LL); // NOLINT(performance-no-int-to-ptr)
    }

    inline const char* il2cpp_field_get_name(FieldInfo* field)
    {
        return *reinterpret_cast<const char**>(field);
    }

    inline Il2CppClass* il2cpp_field_get_parent(FieldInfo* field)
    {
        return *reinterpret_cast<Il2CppClass**>(reinterpret_cast<UINT64>(field) + 16); // NOLINT(performance-no-int-to-ptr)
    }

    inline size_t il2cpp_field_get_offset(FieldInfo* field)
    {
        return reinterpret_cast<size_t(*)(FieldInfo*)>(il2cpp_offsets::il2cpp_field_get_offset)(field);
    }

    inline const Il2CppType* il2cpp_field_get_type(FieldInfo* field)
    {
        return *reinterpret_cast<Il2CppType**>(reinterpret_cast<UINT64>(field) + 8); // NOLINT(performance-no-int-to-ptr)
    }

    inline void il2cpp_field_get_value(
        Il2CppObject* obj, FieldInfo* field, void* value)
    {
        return reinterpret_cast<void(*)(Il2CppObject*, FieldInfo*, void*)>(il2cpp_offsets::il2cpp_field_get_value)(
            obj, field, value);
    }

    inline Il2CppObject* il2cpp_field_get_value_object(
        FieldInfo* field, Il2CppObject* obj)
    {
        return reinterpret_cast<Il2CppObject*(*)(FieldInfo*, Il2CppObject*)>(
            il2cpp_offsets::il2cpp_field_get_value_object)(field, obj);
    }

    inline bool il2cpp_field_has_attribute(
        FieldInfo* field, Il2CppClass* attr_class)
    {
        return reinterpret_cast<bool(*)(FieldInfo*, Il2CppClass*)>(il2cpp_offsets::il2cpp_field_has_attribute)(
            field, attr_class);
    }

    inline void il2cpp_field_set_value(
        Il2CppObject* obj, FieldInfo* field, void* value)
    {
        return reinterpret_cast<void(*)(Il2CppObject*, FieldInfo*, void*)>(il2cpp_offsets::il2cpp_field_set_value)(
            obj, field, value);
    }

    inline void il2cpp_field_static_get_value(
        FieldInfo* field, void* value)
    {
        return reinterpret_cast<void(*)(FieldInfo*, void*, UINT64)>(
            il2cpp_offsets::il2cpp_field_static_get_value)(field, value, 0);
    }

    inline void il2cpp_field_static_set_value(FieldInfo* field, void* value)
    {
        return reinterpret_cast<void(*)(FieldInfo*, void*)>(
            il2cpp_offsets::il2cpp_field_static_set_value)(field, value);
    }

    inline void il2cpp_field_set_value_object(
        Il2CppObject* instance, FieldInfo* field, Il2CppObject* value)
    {
        return reinterpret_cast<void(*)(Il2CppObject*, FieldInfo*, Il2CppObject*)>(
            il2cpp_offsets::il2cpp_field_set_value_object)(
            instance, field, value);
    }

    inline void il2cpp_gc_collect(int maxGenerations)
    {
        return reinterpret_cast<void(*)(int)>(il2cpp_offsets::il2cpp_gc_collect)(maxGenerations);
    }

    inline int32_t il2cpp_gc_collect_a_little()
    {
        return reinterpret_cast<int32_t(*)()>(il2cpp_offsets::il2cpp_gc_collect_a_little)();
    }

    inline void il2cpp_gc_disable()
    {
        return reinterpret_cast<void(*)()>(il2cpp_offsets::il2cpp_gc_disable)();
    }

    inline void il2cpp_gc_enable()
    {
        return reinterpret_cast<void(*)()>(il2cpp_offsets::il2cpp_gc_enable)();
    }

    inline bool il2cpp_gc_is_disabled()
    {
        return reinterpret_cast<bool(*)()>(il2cpp_offsets::il2cpp_gc_is_disabled)();
    }

    inline int64_t il2cpp_gc_get_used_size()
    {
        return reinterpret_cast<int64_t(*)()>(il2cpp_offsets::il2cpp_gc_get_used_size)();
    }

    inline int64_t il2cpp_gc_get_heap_size()
    {
        return reinterpret_cast<int64_t(*)()>(il2cpp_offsets::il2cpp_gc_get_heap_size)();
    }

    inline void il2cpp_gc_wbarrier_set_field(
        Il2CppObject* obj, void** targetAddress, void* object)
    {
        return reinterpret_cast<void(*)(Il2CppObject*, void**, void*)>(il2cpp_offsets::il2cpp_gc_wbarrier_set_field)(
            obj, targetAddress, object);
    }

    inline uint32_t il2cpp_gchandle_new(Il2CppObject* obj, bool pinned)
    {
        return reinterpret_cast<uint32_t(*)(Il2CppObject*, bool)>(il2cpp_offsets::il2cpp_gchandle_new)(obj, pinned);
    }

    inline uint32_t il2cpp_gchandle_new_weakref(
        Il2CppObject* obj, bool track_resurrection)
    {
        return reinterpret_cast<uint32_t(*)(Il2CppObject*, bool)>(il2cpp_offsets::il2cpp_gchandle_new_weakref)(
            obj, track_resurrection);
    }

    inline Il2CppObject* il2cpp_gchandle_get_target(uint32_t gchandle)
    {
        return reinterpret_cast<Il2CppObject*(*)(uint32_t)>(il2cpp_offsets::il2cpp_gchandle_get_target)(gchandle);
    }

    inline void il2cpp_gchandle_free(uint32_t gchandle)
    {
        return reinterpret_cast<void(*)(uint32_t)>(il2cpp_offsets::il2cpp_gchandle_free)(gchandle);
    }

    inline void il2cpp_unity_liveness_calculation_from_root(
        Il2CppObject* root, void* state)
    {
        return reinterpret_cast<void(*)(Il2CppObject*, void*)>(
            il2cpp_offsets::il2cpp_unity_liveness_calculation_from_root)(root, state);
    }

    inline void il2cpp_unity_liveness_calculation_from_statics(void* state)
    {
        return reinterpret_cast<void(*)(void*)>(il2cpp_offsets::il2cpp_unity_liveness_calculation_from_root)(state);
    }

    inline const Il2CppType* il2cpp_method_get_return_type(
        const MethodInfo* method)
    {
        return *reinterpret_cast<Il2CppType**>(reinterpret_cast<UINT64>(method) + 40); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppClass* il2cpp_method_get_declaring_type(
        const MethodInfo* method)
    {
        return *reinterpret_cast<Il2CppClass**>(reinterpret_cast<UINT64>(method) + 32); // NOLINT(performance-no-int-to-ptr)
    }

    inline const char* il2cpp_method_get_name(const MethodInfo* method)
    {
        return *reinterpret_cast<const char**>(reinterpret_cast<UINT64>(method) + 24); // NOLINT(performance-no-int-to-ptr)
    }

    inline const MethodInfo* il2cpp_method_get_from_reflection(
        const Il2CppReflectionMethod* method)
    {
        return *reinterpret_cast<const MethodInfo**>(reinterpret_cast<UINT64>(method) + 16); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppReflectionMethod* il2cpp_method_get_object(
        const MethodInfo* method, Il2CppClass* refclass)
    {
        return reinterpret_cast<Il2CppReflectionMethod*(*)(const MethodInfo*, Il2CppClass*)>(
            il2cpp_offsets::il2cpp_method_get_object)(method, refclass);
    }

    inline bool il2cpp_method_is_generic(const MethodInfo* method)
    {
        return reinterpret_cast<bool(*)(const MethodInfo*)>(il2cpp_offsets::il2cpp_method_is_generic)(method);
    }

    inline bool il2cpp_method_is_inflated(const MethodInfo* method)
    {
        return reinterpret_cast<bool(*)(const MethodInfo*)>(il2cpp_offsets::il2cpp_method_is_inflated)(method);
    }

    inline bool il2cpp_method_is_instance(const MethodInfo* method)
    {
        return reinterpret_cast<bool(*)(const MethodInfo*)>(il2cpp_offsets::il2cpp_method_is_instance)(method);
    }

    inline uint32_t il2cpp_method_get_param_count(const MethodInfo* method)
    {
        return *reinterpret_cast<uint8_t*>(reinterpret_cast<UINT64>(method) + 82); // NOLINT(performance-no-int-to-ptr)
    }

    inline const Il2CppType* il2cpp_method_get_param(
        const MethodInfo* method, uint32_t index)
    {
        return reinterpret_cast<Il2CppType*(*)(const MethodInfo*, uint32_t)>(
            il2cpp_offsets::il2cpp_method_get_param)(method, index);
    }

    inline Il2CppClass* il2cpp_method_get_class(const MethodInfo* method)
    {
        return *reinterpret_cast<Il2CppClass**>(reinterpret_cast<UINT64>(method) + 32); // NOLINT(performance-no-int-to-ptr)
    }

    inline bool il2cpp_method_has_attribute(
        const MethodInfo* method, Il2CppClass* attr_class)
    {
        return reinterpret_cast<bool(*)(const MethodInfo*, Il2CppClass*)>(il2cpp_offsets::il2cpp_method_has_attribute)(
            method, attr_class);
    }

    inline uint32_t il2cpp_method_get_flags(
        const MethodInfo* method, uint32_t* iflags)
    {
        if (iflags)
        {
            *iflags = *reinterpret_cast<uint16_t*>(reinterpret_cast<UINT64>(method) + 78); // NOLINT(performance-no-int-to-ptr)
        }
        return *reinterpret_cast<uint16_t*>(reinterpret_cast<UINT64>(method) + 76); // NOLINT(performance-no-int-to-ptr)
    }

    inline uint32_t il2cpp_method_get_token(const MethodInfo* method)
    {
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<UINT64>(method) + 72); // NOLINT(performance-no-int-to-ptr)
    }

    inline const char* il2cpp_method_get_param_name(
        const MethodInfo* method, uint32_t index)
    {
        return reinterpret_cast<const char*(*)(const MethodInfo*, uint32_t)>(
            il2cpp_offsets::il2cpp_method_get_param_name)(method, index);
    }

    inline uint32_t il2cpp_property_get_flags(PropertyInfo* prop)
    {
        return reinterpret_cast<uint32_t(*)(PropertyInfo*)>(il2cpp_offsets::il2cpp_property_get_flags)(prop);
    }

    inline const MethodInfo* il2cpp_property_get_get_method(
        PropertyInfo* prop)
    {
        return *reinterpret_cast<const MethodInfo**>(reinterpret_cast<UINT64>(prop) + 16); // NOLINT(performance-no-int-to-ptr)
    }

    inline const MethodInfo* il2cpp_property_get_set_method(
        PropertyInfo* prop)
    {
        return *reinterpret_cast<const MethodInfo**>(reinterpret_cast<UINT64>(prop) + 24); // NOLINT(performance-no-int-to-ptr)
    }

    inline const char* il2cpp_property_get_name(PropertyInfo* prop)
    {
        return *reinterpret_cast<const char**>(reinterpret_cast<UINT64>(prop) + 8); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppClass* il2cpp_property_get_parent(PropertyInfo* prop)
    {
        return reinterpret_cast<Il2CppClass*(*)(PropertyInfo*)>(il2cpp_offsets::il2cpp_property_get_parent)(prop);
    }

    inline Il2CppClass* il2cpp_object_get_class(Il2CppObject* obj)
    {
        return reinterpret_cast<Il2CppClass*(*)(Il2CppObject*)>(il2cpp_offsets::il2cpp_object_get_class)(obj);
    }

    inline uint32_t il2cpp_object_get_size(Il2CppObject* obj)
    {
        return reinterpret_cast<uint32_t(*)(Il2CppObject*)>(il2cpp_offsets::il2cpp_object_get_size)(obj);
    }

    inline const MethodInfo* il2cpp_object_get_virtual_method(
        Il2CppObject* obj, const MethodInfo* method)
    {
        return reinterpret_cast<const MethodInfo*(*)(Il2CppObject*, const MethodInfo*)>(
            il2cpp_offsets::il2cpp_object_get_virtual_method)(obj, method);
    }

    inline Il2CppObject* il2cpp_object_new(const Il2CppClass* klass)
    {
        return reinterpret_cast<Il2CppObject*(*)(const Il2CppClass*)>(il2cpp_offsets::il2cpp_object_new)(klass);
    }

    inline void* il2cpp_object_unbox(Il2CppObject* obj)
    {
        return reinterpret_cast<PVOID>(reinterpret_cast<UINT64>(obj) + 16); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppObject* il2cpp_value_box(Il2CppClass* klass, void* data)
    {
        return reinterpret_cast<Il2CppObject*(*)(Il2CppClass*, void*)>(il2cpp_offsets::il2cpp_value_box)(klass, data);
    }

    inline void il2cpp_monitor_enter(Il2CppObject* obj)
    {
        return reinterpret_cast<void(*)(Il2CppObject*, PVOID)>(il2cpp_offsets::il2cpp_monitor_enter)(
            obj, reinterpret_cast<PVOID>(0xFFFFFFFFLL));
    }

    inline bool il2cpp_monitor_try_enter(Il2CppObject* obj, uint32_t timeout)
    {
        return reinterpret_cast<bool(*)(Il2CppObject*, uint32_t)>(il2cpp_offsets::il2cpp_monitor_try_enter)(
            obj, timeout);
    }

    inline void il2cpp_monitor_exit(Il2CppObject* obj)
    {
        return reinterpret_cast<void(*)(Il2CppObject*)>(il2cpp_offsets::il2cpp_monitor_enter)(obj);
    }

    inline void il2cpp_monitor_pulse(Il2CppObject* obj)
    {
        return reinterpret_cast<void(*)(Il2CppObject*)>(il2cpp_offsets::il2cpp_monitor_enter)(obj);
    }

    inline void il2cpp_monitor_pulse_all(Il2CppObject* obj)
    {
        return reinterpret_cast<void(*)(Il2CppObject*)>(il2cpp_offsets::il2cpp_monitor_enter)(obj);
    }

    inline void il2cpp_monitor_wait(Il2CppObject* obj)
    {
        return reinterpret_cast<void(*)(Il2CppObject*)>(il2cpp_offsets::il2cpp_monitor_enter)(obj);
    }

    inline bool il2cpp_monitor_try_wait(Il2CppObject* obj, uint32_t timeout)
    {
        return reinterpret_cast<bool(*)(Il2CppObject*, uint32_t)>(il2cpp_offsets::il2cpp_monitor_try_enter)(
            obj, timeout);
    }

    inline Il2CppObject*
    il2cpp_runtime_invoke(const MethodInfo* method, void* obj, void** params, Il2CppException** exc)
    {
        return reinterpret_cast<Il2CppObject*(*)(const MethodInfo*, void*, void**, Il2CppException**)>(
            il2cpp_offsets::il2cpp_runtime_invoke)(method, obj, params, exc);
    }

    inline Il2CppObject* il2cpp_runtime_invoke_convert_args(
        const MethodInfo* method, void* obj,
        Il2CppObject** params, int paramCount,
        Il2CppException** exc)
    {
        return reinterpret_cast<Il2CppObject*(*)(const MethodInfo*, void*, Il2CppObject**, int paramCount,
                                                 Il2CppException**)>(
            il2cpp_offsets::il2cpp_runtime_invoke_convert_args)(
            method, obj, params, paramCount, exc);
    }

    inline void il2cpp_runtime_class_init(Il2CppClass* klass)
    {
        return reinterpret_cast<void(*)(Il2CppClass*)>(il2cpp_offsets::il2cpp_runtime_class_init)(klass);
    }

    inline void il2cpp_runtime_object_init(Il2CppObject* obj)
    {
        return reinterpret_cast<void(*)(Il2CppObject*)>(il2cpp_offsets::il2cpp_runtime_class_init)(obj);
    }

    inline void il2cpp_runtime_object_init_exception(
        Il2CppObject* obj, Il2CppException** exc)
    {
        return reinterpret_cast<void(*)(Il2CppObject*, Il2CppException**)>(
            il2cpp_offsets::il2cpp_runtime_object_init_exception)(obj, exc);
    }

    inline void il2cpp_runtime_unhandled_exception_policy_set(
        Il2CppRuntimeUnhandledExceptionPolicy value)
    {
        return reinterpret_cast<void(*)(Il2CppRuntimeUnhandledExceptionPolicy)>(
            il2cpp_offsets::il2cpp_runtime_unhandled_exception_policy_set)(value);
    }

    inline int32_t il2cpp_string_length(Il2CppString* str)
    {
        return *reinterpret_cast<int32_t*>(reinterpret_cast<UINT64>(str) + 16); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppChar* il2cpp_string_chars(Il2CppString* str)
    {
        return reinterpret_cast<Il2CppChar*>(reinterpret_cast<UINT64>(str) + 20); // NOLINT(performance-no-int-to-ptr)
    }

    inline Il2CppString* il2cpp_string_new(const char* str)
    {
        return reinterpret_cast<Il2CppString*(*)(const char*)>(il2cpp_offsets::il2cpp_string_new)(str);
    }

    inline Il2CppString* il2cpp_string_new_len(
        const char* str, uint32_t length)
    {
        return reinterpret_cast<Il2CppString*(*)(const char*, uint32_t)>(
            il2cpp_offsets::il2cpp_string_new_len)(str, length);
    }

    inline Il2CppString* il2cpp_string_new_utf16(
        const Il2CppChar* text, int32_t len)
    {
        return reinterpret_cast<Il2CppString*(*)(const Il2CppChar*, int32_t)>(
            il2cpp_offsets::il2cpp_string_new_utf16)(text, len);
    }

    inline Il2CppString* il2cpp_string_new_wrapper(const char* str)
    {
        return reinterpret_cast<Il2CppString*(*)(const char*)>(il2cpp_offsets::il2cpp_string_new_wrapper)(str);
    }

    inline Il2CppString* il2cpp_string_intern(Il2CppString* str)
    {
        return reinterpret_cast<Il2CppString*(*)(Il2CppString*)>(il2cpp_offsets::il2cpp_string_intern)(str);
    }

    inline Il2CppString* il2cpp_string_is_interned(Il2CppString* str)
    {
        return reinterpret_cast<Il2CppString*(*)(Il2CppString*)>(il2cpp_offsets::il2cpp_string_is_interned)(str);
    }

    inline Il2CppThread* il2cpp_thread_current()
    {
        return reinterpret_cast<Il2CppThread*(*)()>(il2cpp_offsets::il2cpp_thread_current)();
    }

    inline Il2CppThread* il2cpp_thread_attach(Il2CppDomain* domain)
    {
        return reinterpret_cast<Il2CppThread*(*)(Il2CppDomain*)>(il2cpp_offsets::il2cpp_thread_attach)(domain);
    }

    inline void il2cpp_thread_detach(Il2CppThread* thread)
    {
        return reinterpret_cast<void(*)(Il2CppThread*)>(il2cpp_offsets::il2cpp_thread_detach)(thread);
    }

    inline Il2CppThread** il2cpp_thread_get_all_attached_threads(size_t* size)
    {
        return reinterpret_cast<Il2CppThread**(*)(size_t*)>(
            il2cpp_offsets::il2cpp_thread_get_all_attached_threads)(size);
    }

    inline bool il2cpp_is_vm_thread(Il2CppThread* thread)
    {
        return reinterpret_cast<bool(*)(Il2CppThread*)>(il2cpp_offsets::il2cpp_is_vm_thread)(thread);
    }

    inline void il2cpp_current_thread_walk_frame_stack(
        Il2CppFrameWalkFunc func, void* user_data)
    {
        return reinterpret_cast<void(*)(Il2CppFrameWalkFunc, void*)>(
            il2cpp_offsets::il2cpp_current_thread_walk_frame_stack)(
            func, user_data);
    }

    inline void il2cpp_thread_walk_frame_stack(
        Il2CppThread* thread, Il2CppFrameWalkFunc func, void* user_data)
    {
        return reinterpret_cast<void(*)(Il2CppThread*, Il2CppFrameWalkFunc, void*)>(
            il2cpp_offsets::il2cpp_thread_walk_frame_stack)(thread, func, user_data);
    }

    inline bool il2cpp_current_thread_get_top_frame(
        Il2CppStackFrameInfo* frame)
    {
        return reinterpret_cast<bool(*)(Il2CppStackFrameInfo*)>(
            il2cpp_offsets::il2cpp_current_thread_get_top_frame)(frame);
    }

    inline bool il2cpp_thread_get_top_frame(
        Il2CppThread* thread, Il2CppStackFrameInfo* frame)
    {
        return reinterpret_cast<bool(*)(Il2CppThread*, Il2CppStackFrameInfo*)>(
            il2cpp_offsets::il2cpp_thread_get_top_frame)(thread, frame);
    }

    inline bool il2cpp_current_thread_get_frame_at(
        int32_t offset, Il2CppStackFrameInfo* frame)
    {
        return reinterpret_cast<bool(*)(int32_t, Il2CppStackFrameInfo*)>(
            il2cpp_offsets::il2cpp_current_thread_get_frame_at)(offset, frame);
    }

    inline bool il2cpp_thread_get_frame_at(
        Il2CppThread* thread, int32_t offset, Il2CppStackFrameInfo* frame)
    {
        return reinterpret_cast<bool(*)(Il2CppThread*, int32_t, Il2CppStackFrameInfo*)>(
            il2cpp_offsets::il2cpp_thread_get_frame_at)(thread, offset, frame);
    }

    inline int32_t il2cpp_current_thread_get_stack_depth()
    {
        return reinterpret_cast<int32_t(*)()>(il2cpp_offsets::il2cpp_current_thread_get_stack_depth)();
    }

    inline int32_t il2cpp_thread_get_stack_depth(Il2CppThread* thread)
    {
        return reinterpret_cast<int32_t(*)(Il2CppThread*)>(il2cpp_offsets::il2cpp_thread_get_stack_depth)(thread);
    }

    inline Il2CppObject* il2cpp_type_get_object(const Il2CppType* type)
    {
        return reinterpret_cast<Il2CppObject*(*)(const Il2CppType*)>(il2cpp_offsets::il2cpp_type_get_object)(type);
    }

    inline int il2cpp_type_get_type(const Il2CppType* type)
    {
        return reinterpret_cast<int(*)(const Il2CppType*)>(il2cpp_offsets::il2cpp_type_get_type)(type);
    }

    inline Il2CppClass* il2cpp_type_get_class_or_element_class(
        const Il2CppType* type)
    {
        return reinterpret_cast<Il2CppClass*(*)(const Il2CppType*)>(
            il2cpp_offsets::il2cpp_type_get_class_or_element_class)(type);
    }

    inline char* il2cpp_type_get_name(const Il2CppType* type)
    {
        return reinterpret_cast<char*(*)(const Il2CppType*)>(il2cpp_offsets::il2cpp_type_get_name)(type);
    }

    inline bool il2cpp_type_is_byref(const Il2CppType* type)
    {
        return reinterpret_cast<bool(*)(const Il2CppType*)>(il2cpp_offsets::il2cpp_type_is_byref)(type);
    }

    inline uint32_t il2cpp_type_get_attrs(const Il2CppType* type)
    {
        return reinterpret_cast<uint32_t(*)(const Il2CppType*)>(il2cpp_offsets::il2cpp_type_get_attrs)(type);
    }

    inline bool il2cpp_type_equals(
        const Il2CppType* type, const Il2CppType* otherType)
    {
        return reinterpret_cast<uint32_t(*)(const Il2CppType*, const Il2CppType*)>(
            il2cpp_offsets::il2cpp_type_equals)(type, otherType) == 0;
    }

    inline char* il2cpp_type_get_assembly_qualified_name(
        const Il2CppType* type)
    {
        return reinterpret_cast<char*(*)(const Il2CppType*)>(
            il2cpp_offsets::il2cpp_type_get_assembly_qualified_name)(type);
    }

    inline const Il2CppAssembly* il2cpp_image_get_assembly(
        const Il2CppImage* image)
    {
        return *reinterpret_cast<Il2CppAssembly**>(reinterpret_cast<UINT64>(image) + 16); // NOLINT(performance-no-int-to-ptr)
    }

    inline const char* il2cpp_image_get_name(const Il2CppImage* image)
    {
        return reinterpret_cast<const char*(*)(const Il2CppImage*)>(il2cpp_offsets::il2cpp_image_get_name)(image);
    }

    inline const char* il2cpp_image_get_filename(const Il2CppImage* image)
    {
        return reinterpret_cast<const char*(*)(const Il2CppImage*)>(il2cpp_offsets::il2cpp_image_get_filename)(image);
    }

    inline const MethodInfo* il2cpp_image_get_entry_point(
        const Il2CppImage* image)
    {
        return reinterpret_cast<MethodInfo*(*)(const Il2CppImage*)>(
            il2cpp_offsets::il2cpp_image_get_entry_point)(image);
    }

    inline size_t il2cpp_image_get_class_count(const Il2CppImage* image)
    {
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<UINT64>(image) + 24); // NOLINT(performance-no-int-to-ptr)
    }

    inline const Il2CppClass* il2cpp_image_get_class(
        const Il2CppImage* image, size_t index)
    {
        return reinterpret_cast<Il2CppClass*(*)(const Il2CppImage*, size_t)>(
            il2cpp_offsets::il2cpp_image_get_class)(image, index);
    }

    inline Il2CppManagedMemorySnapshot* il2cpp_capture_memory_snapshot()
    {
        return reinterpret_cast<Il2CppManagedMemorySnapshot*(*)()>(il2cpp_offsets::il2cpp_capture_memory_snapshot)();
    }

    inline void il2cpp_free_captured_memory_snapshot(
        Il2CppManagedMemorySnapshot* snapshot)
    {
        return reinterpret_cast<void(*)(Il2CppManagedMemorySnapshot*)>(
            il2cpp_offsets::il2cpp_free_captured_memory_snapshot)(snapshot);
    }

    inline void il2cpp_set_find_plugin_callback(
        Il2CppSetFindPlugInCallback method)
    {
        return reinterpret_cast<void(*)(Il2CppSetFindPlugInCallback)>(
            il2cpp_offsets::il2cpp_set_find_plugin_callback)(method);
    }

    inline void il2cpp_register_log_callback(Il2CppLogCallback method)
    {
        return reinterpret_cast<void(*)(Il2CppLogCallback)>(il2cpp_offsets::il2cpp_register_log_callback)(method);
    }

    inline void il2cpp_debugger_set_agent_options(const char* options)
    {
        return reinterpret_cast<void(*)(const char*)>(il2cpp_offsets::il2cpp_debugger_set_agent_options)(options);
    }

    inline bool il2cpp_is_debugger_attached()
    {
        return IsDebuggerPresent();
    }

    inline void il2cpp_unity_install_unitytls_interface(
        const void* unitytlsInterfaceStruct)
    {
        return reinterpret_cast<void(*)(const void*)>(il2cpp_offsets::il2cpp_unity_install_unitytls_interface)(
            unitytlsInterfaceStruct);
    }

    inline Il2CppCustomAttrInfo* il2cpp_custom_attrs_from_class(
        Il2CppClass* klass)
    {
        return reinterpret_cast<Il2CppCustomAttrInfo*(*)(Il2CppClass*)>(
            il2cpp_offsets::il2cpp_custom_attrs_from_class)(klass);
    }

    inline Il2CppCustomAttrInfo* il2cpp_custom_attrs_from_method(
        const MethodInfo* method)
    {
        return reinterpret_cast<Il2CppCustomAttrInfo*(*)(const MethodInfo*)>(
            il2cpp_offsets::il2cpp_custom_attrs_from_method)(method);
    }

    inline Il2CppObject* il2cpp_custom_attrs_get_attr(
        Il2CppCustomAttrInfo* ainfo, Il2CppClass* attr_klass)
    {
        return reinterpret_cast<Il2CppObject*(*)(Il2CppCustomAttrInfo*, Il2CppClass*)>(
            il2cpp_offsets::il2cpp_custom_attrs_get_attr)(ainfo, attr_klass);
    }

    inline bool il2cpp_custom_attrs_has_attr(
        Il2CppCustomAttrInfo* ainfo, Il2CppClass* attr_klass)
    {
        return reinterpret_cast<bool(*)(Il2CppCustomAttrInfo*, Il2CppClass*)>(
            il2cpp_offsets::il2cpp_custom_attrs_has_attr)(
            ainfo, attr_klass);
    }

    inline Il2CppArray* il2cpp_custom_attrs_construct(
        Il2CppCustomAttrInfo* cinfo)
    {
        return reinterpret_cast<Il2CppArray*(*)(Il2CppCustomAttrInfo*)>(
            il2cpp_offsets::il2cpp_custom_attrs_construct)(cinfo);
    }

    inline void il2cpp_custom_attrs_free(Il2CppCustomAttrInfo* ainfo)
    {
        return reinterpret_cast<void(*)(Il2CppCustomAttrInfo*)>(il2cpp_offsets::il2cpp_custom_attrs_free)(ainfo);
    }
}
