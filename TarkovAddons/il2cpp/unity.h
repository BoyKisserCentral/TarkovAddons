#pragma once
#include "libil2cpp/il2cpp-api-types.h"
#include <Windows.h>

#include "libil2cpp/il2cpp-object-internals.h"
#include "il2utils.h"

namespace unity
{
    using find_objects_of_type_sig = Il2CppArray*(*)(PVOID);
    static find_objects_of_type_sig find_objects_of_type_internal = nullptr;
    using find_object_of_type_sig = Il2CppObject*(*)(PVOID);
    static find_object_of_type_sig find_object_of_type_internal = nullptr;
    using get_name_sig = Il2CppString*(*)(Il2CppObject*);
    static get_name_sig get_name_internal = nullptr;

    inline void init()
    {
        Il2CppImage* unity_engine = il2utils::resolve_image("UnityEngine.CoreModule.dll");
        const Il2CppClass* object = il2utils::resolve_class(unity_engine, "UnityEngine", "Object");

        find_objects_of_type_internal = il2utils::get_method<find_objects_of_type_sig>(object, "FindObjectsOfType", 1);
        find_object_of_type_internal = il2utils::get_method<find_object_of_type_sig>(object, "FindObjectOfType", 1);
        get_name_internal = il2utils::get_method<get_name_sig>(object, "GetName", 1);
    }

    inline Il2CppObject** find_objects_of_type(Il2CppObject* type, _Out_ size_t* amount)
    {
        Il2CppArray* array = find_objects_of_type_internal(type);
        *amount = array->max_length;
        return reinterpret_cast<Il2CppObject**>(&array->data);
    }

    inline Il2CppObject* find_object_of_type(Il2CppObject* type)
    {
        return find_object_of_type_internal(type);
    }

    inline std::string get_name(Il2CppObject* object)
    {
        Il2CppString* name = get_name_internal(object);
        std::stringstream ss;
        for (int i = 0; i < name->length; ++i)
        {
            ss << static_cast<char>(name->chars[i]);
        }
        return ss.str();
    }
}
