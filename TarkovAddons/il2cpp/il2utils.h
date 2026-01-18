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

    struct CACHE_NESTED_CLASS_DESC
    {
        const Il2CppClass* parent;
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
    static auto inline nested_cache = std::unordered_map<size_t, const Il2CppClass*>();
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

    inline const Il2CppClass* resolve_class_nested(const Il2CppClass* parent, const char* name)
    {
        CACHE_NESTED_CLASS_DESC desc = {.parent = parent, .clazz = Hash::get(name)};
        auto iter = nested_cache.find(utils::hash_struct(desc));
        if (iter != nested_cache.end()) return iter->second;

        void* n_iter = nullptr;
        Il2CppClass* nested;
        while ((nested = il2cpp::il2cpp_class_get_nested_types(const_cast<Il2CppClass*>(parent), &n_iter)))
        {
            if (std::string(nested->name) == std::string(name))
            {
                return nested;
            }
        }
        return nullptr;
    }

    inline const Il2CppClass* resolve_class(const Il2CppImage* image, const char* namespaze, const char* name)
    {
        CACHE_CLASS_DESC desc = {.image = image, .namespaze = Hash::get(namespaze), .clazz = Hash::get(name)};
        auto iter = class_cache.find(utils::hash_struct(desc));
        if (iter != class_cache.end()) return iter->second;

        return il2cpp::il2cpp_class_from_name(image, namespaze, name);
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
        il2cpp::il2cpp_field_static_get_value(field, &value);
        return value;
    }

    template <typename T>
    T get_method(const Il2CppClass* clazz, const char* name, const int args)
    {
        const MethodInfo* method = resolve_method(clazz, name, args);
        return static_cast<T>(method->methodPointer); // NOLINT(clang-diagnostic-microsoft-cast)
    }

    template <typename T, typename T2>
    void hook_method(const Il2CppClass* clazz, const char* name, const int args, T hook, T2 original)
    {
        const MethodInfo* method = resolve_method(clazz, name, args);
        hooks::hook(method->methodPointer, reinterpret_cast<PVOID>(hook), reinterpret_cast<PVOID*>(original));
    }

    template <typename T, typename T2>
    void unhook_method(const Il2CppClass* clazz, const char* name, const int args, T hook, T2 original)
    {
        const MethodInfo* method = resolve_method(clazz, name, args);
        hooks::unhook(method->methodPointer, reinterpret_cast<PVOID>(hook), reinterpret_cast<PVOID*>(original));
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

    inline Il2CppClass* inflate(const Il2CppClass* clazz, const std::vector<const Il2CppClass*>& types)
    {
        Il2CppObject* system_type = il2cpp::il2cpp_type_get_object(il2cpp::il2cpp_class_get_type(const_cast<
            Il2CppClass*>(clazz)));
        auto system_type_args = std::vector<Il2CppObject*>();
        for (auto type : types)
        {
            system_type_args.push_back(il2cpp::il2cpp_type_get_object(il2cpp::il2cpp_class_get_type(const_cast<
                Il2CppClass*>(type))));
        }

        Il2CppImage* corlib = resolve_image("mscorlib.dll");
        const Il2CppClass* type_class = resolve_class(corlib, "System", "RuntimeType");
        Il2CppArray* array =
            il2cpp::il2cpp_array_new(const_cast<Il2CppClass*>(type_class),
                                     system_type_args.size());
        for (size_t i = 0; i < system_type_args.size(); ++i)
        {
            reinterpret_cast<Il2CppObject**>(&array->data)[i] = system_type_args.at(i);
        }

        auto make_generic_type = il2utils::get_method<Il2CppReflectionType*(*)(
            Il2CppObject*, Il2CppObject*)>(
            type_class, "MakeGenericType", 1);

        auto inflated_type = make_generic_type(system_type, array);

        return il2cpp::il2cpp_class_from_system_type(inflated_type);
    }

    inline std::string conv_string(const Il2CppString* string)
    {
        std::stringstream ss;
        for (int i = 0; i < string->length; ++i)
        {
            ss << static_cast<char>(string->chars[i]);
        }
        return ss.str();
    }

    inline std::wstring conv_wstring(const Il2CppString* string)
    {
        std::wstringstream ss;
        for (int i = 0; i < string->length; ++i)
        {
            ss << string->chars[i];
        }
        return ss.str();
    }
}
