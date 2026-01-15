#pragma once
#include "ConfigValue.h"
#include "../gui/menu/imgui_addons.h"

class FloatSliderValue : public ConfigValue
{
public:
    FloatSliderValue(float initial, float min, float max, const std::string& n) : ConfigValue(
        this->to_string(initial), n, this->to_string(initial))
    {
        this->min = min;
        this->max = max;
    }

    float min;
    float max;

    std::string to_string(float v)
    {
        return std::to_string(v);
    }

    float from_string(std::string string)
    {
        return std::stof(string);
    }

    float get_val()
    {
        return this->from_string(this->value);
    }

    void draw() override
    {
        float f = this->from_string(this->value);
        imgui_addons::slider_float(this->imgui_name, &f, this->min, this->max);
        this->value = this->to_string(f);
    }
};
