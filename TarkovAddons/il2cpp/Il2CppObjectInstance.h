#pragma once
#include "libil2cpp/il2cpp-class-internals.h"
#include "il2utils.h"

class Il2CppObjectInstance
{
public:
    static Il2CppObjectInstance* create(const Il2CppImage* image, const char* namespaze, const char* name,
                                        Il2CppObject* instance)
    {
        const Il2CppClass* clazz = il2utils::resolve_class(image, namespaze, name);
        return new Il2CppObjectInstance(clazz, instance);
    }

    Il2CppObjectInstance(const Il2CppClass* clazz, Il2CppObject* instance)
    {
        this->clazz_ = clazz;
        this->instance_ = instance;
    }

    template <typename T>
    void set_field(const char* name, T value)
    {
        FieldInfo* field = il2utils::resolve_field(this->clazz_, name);
        *static_cast<T*>(instance_ + field->offset) = value;
    }

    template <typename T>
    T get_field(const char* name)
    {
        FieldInfo* field = il2utils::resolve_field(this->clazz_, name);
        return *static_cast<T*>(instance_ + field->offset);
    }

    template <typename T>
    T get_method(const char* name, const int args)
    {
        return il2utils::get_method<T>(this->clazz_, name, args);
    }

private:
    const Il2CppClass* clazz_;
    Il2CppObject* instance_;
};
