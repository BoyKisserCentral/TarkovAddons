#pragma once
#include <any>
#include <imgui.h>
#include <vector>

#include "ModuleCategory.h"
#include "../config/ConfigValue.h"

class Module
{
public:
    virtual ~Module() = default;

    Module(std::string name, ModuleCategory category)
    {
        this->name = name;
        this->category = category;
    }

    std::string name;
    ModuleCategory category;

    virtual void draw_overlay(ImDrawList* draw_list) = 0;
    virtual void init() = 0;

    std::vector<ConfigValue*> config_values = std::vector<ConfigValue*>();

    void apply(const std::function<void (ConfigValue*)>& function) const
    {
        for (auto config_value : config_values)
        {
            function(config_value);
        }
    }

    template <typename T>
    T* conf(T* value)
    {
        value->reg(this->name);
        config_values.push_back(value);
        return value;
    }
};
