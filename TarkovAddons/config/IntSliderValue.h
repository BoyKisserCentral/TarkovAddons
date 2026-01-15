#pragma once
#include "ConfigValue.h"
#include "../gui/menu/imgui_addons.h"

class IntSliderValue : public ConfigValue
{
public:
    IntSliderValue(int initial, int min, int max, const std::string& n) : ConfigValue(
        this->to_string(initial), n, this->to_string(initial))
    {
        this->min = min;
        this->max = max;
    }

    int min;
    int max;

    std::string to_string(int v)
    {
        return std::to_string(v);
    }

    int from_string(std::string string)
    {
        return std::stoi(string);
    }

    int get_val()
    {
        return this->from_string(this->value);
    }

    void draw() override
    {
        int i = this->from_string(this->value);
        imgui_addons::slider_int(this->imgui_name, &i, this->min, this->max);
        this->value = this->to_string(i);
    }
};
