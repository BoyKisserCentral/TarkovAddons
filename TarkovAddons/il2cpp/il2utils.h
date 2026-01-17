#pragma once
#include <unordered_map>
#include <Windows.h>

#include "exports.h"
#include "../hooks/hooks.h"
#include "../util/hash.h"
#include "../util/utils.h"

namespace il2utils
{
    struct CACHE_CLASS_DESC
    {
        const Il2CppImage* image;
        size_t namespaze;
        size_t clazz;
    };

    struct CACHE_FIELD_DESC
    {
        const Il2CppClass* clazz;
        size_t field;
    };

    struct CACHE_METHOD_DESC // NOLINT(clang-diagnostic-padded)
    {
        const Il2CppClass* clazz;
        size_t field;
        int arg_count;
    };

    static auto inline image_cache = std::unordered_map<size_t, Il2CppImage*>();
    static auto inline class_cache = std::unordered_map<size_t, const Il2CppClass*>();
    static auto inline field_cache = std::unordered_map<size_t, FieldInfo*>();
    static auto inline method_cache = std::unordered_map<size_t, const MethodInfo*>();
    static auto inline system_type_cache = std::unordered_map<size_t, Il2CppObject*>();

    inline Il2CppImage* resolve_image(const char* name)
    {
        size_t hash = Hash::get(name);
        auto iter = image_cache.find(hash);
        if (iter != image_cache.end()) return iter->second;

        Il2CppDomain* domain = il2cpp::il2cpp_domain_get();
        size_t assemblies_size = 0;
        const Il2CppAssembly** assemblies = il2cpp::il2cpp_domain_get_assemblies(domain, &assemblies_size);
        for (size_t i = 0; i < assemblies_size; ++i)
        {
            Il2CppImage* image = assemblies[i]->image;
            if (std::string(image->name) == std::string(name))
            {
                image_cache.emplace(hash, image);
                return image;
            }
        }

        return nullptr;
    }

    inline const Il2CppClass* resolve_class(const Il2CppImage* image, const char* namespaze, const char* name)
    {
        CACHE_CLASS_DESC desc = {.image = image, .namespaze = Hash::get(namespaze), .clazz = Hash::get(name)};
        auto iter = class_cache.find(utils::hash_struct(desc));
        if (iter != class_cache.end()) return iter->second;

        size_t class_count = il2cpp::il2cpp_image_get_class_count(image);
        for (size_t i = 0; i < class_count; ++i)
        {
            const Il2CppClass* clazz = il2cpp::il2cpp_image_get_class(image, i);
            if (std::string(clazz->namespaze) == std::string(namespaze) && std::string(clazz->name) ==
                std::string(name))
            {
                class_cache.emplace(utils::hash_struct(desc), clazz);
                return clazz;
            }
        }

        return nullptr;
    }

    inline FieldInfo* resolve_field(const Il2CppClass* clazz, const char* name)
    {
        CACHE_FIELD_DESC desc = {.clazz = clazz, .field = Hash::get(name)};
        auto iter = field_cache.find(utils::hash_struct(desc));
        if (iter != field_cache.end()) return iter->second;

        FieldInfo* field = il2cpp::il2cpp_class_get_field_from_name(const_cast<Il2CppClass*>(clazz), name);
        field_cache.emplace(utils::hash_struct(desc), field);
        return field;
    }

    inline const MethodInfo* resolve_method(const Il2CppClass* clazz, const char* name, int arg_count)
    {
        CACHE_METHOD_DESC desc = {.clazz = clazz, .field = Hash::get(name), .arg_count = arg_count};
        auto iter = method_cache.find(utils::hash_struct(desc));
        if (iter != method_cache.end()) return iter->second;

        const MethodInfo* method = il2cpp::il2cpp_class_get_method_from_name(
            const_cast<Il2CppClass*>(clazz), name, arg_count);
        method_cache.emplace(utils::hash_struct(desc), method);
        return method;
    }

    template <typename T>
    void set_static_field(const Il2CppClass* clazz, const char* name, T value)
    {
        FieldInfo* field = resolve_field(clazz, name);
        il2cpp_field_static_set_value(field, &value);
    }

    template <typename T>
    T get_static_field(const Il2CppClass* clazz, const char* name)
    {
        FieldInfo* field = resolve_field(clazz, name);
        T value;
        il2cpp_field_static_get_value(field, &value);
        return value;
    }

    template <typename T>
    T get_method(const Il2CppClass* clazz, const char* name, const int args)
    {
        const MethodInfo* method = resolve_method(clazz, name, args);
        return static_cast<T>(method->methodPointer); // NOLINT(clang-diagnostic-microsoft-cast)
    }

    template <typename T>
    void hook_method(const Il2CppClass* clazz, const char* name, int args, T hook, PVOID* original)
    {
        const MethodInfo* method = resolve_method(clazz, name, args);
        hooks::hook(method->methodPointer, hook, original);
    }

    template <typename T>
    void unhook_method(const Il2CppClass* clazz, const char* name, int args, T hook, PVOID* original)
    {
        const MethodInfo* method = resolve_method(clazz, name, args);
        hooks::unhook(method->methodPointer, hook, original);
    }

    inline Il2CppObject* get_system_type(const Il2CppImage* image, const char* namespaze, const char* name)
    {
        CACHE_CLASS_DESC desc = {.image = image, .namespaze = Hash::get(namespaze), .clazz = Hash::get(name)};
        auto iter = system_type_cache.find(utils::hash_struct(desc));
        if (iter != system_type_cache.end()) return iter->second;

        const Il2CppType* type = il2cpp::il2cpp_class_get_type(
            const_cast<Il2CppClass*>(resolve_class(image, namespaze, name)));
        return il2cpp::il2cpp_type_get_object(type);
    }
}
