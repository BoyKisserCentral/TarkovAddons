#pragma once
#include "ConfigValue.h"
#include "../gui/menu/imgui_addons.h"

class TextboxValue : public ConfigValue
{
public:
    // ReSharper disable once CppPassValueParameterByConstReference
    TextboxValue(const std::string& initial, std::string n) : ConfigValue( // NOLINT(performance-unnecessary-value-param)
        initial, n, initial)
    {
    }

    std::string get_val()
    {
        return this->value;
    }

    void draw() override
    {
        imgui_addons::textbox(this->imgui_name, &this->value);
    }
};
