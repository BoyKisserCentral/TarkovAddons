#pragma once
#include <imgui.h>
#include <sstream>
#include <vector>

#include "ConfigValue.h"
#include "../gui/menu/imgui_addons.h"
#include "../util/utils.h"

class ColorpickerValue : public ConfigValue
{
public:
    ColorpickerValue(ImVec4 initial, const std::string& n) : ConfigValue(
        this->to_string(initial), n, this->to_string(initial))
    {
    }

    std::string to_string(ImVec4 v)
    {
        std::stringstream ss;
        ss << v.x << "|" << v.y << "|" << v.z << "|" << v.w;
        return ss.str();
    }

    ImVec4 from_string(std::string string)
    {
        std::vector<std::string> elements = utils::split(string, '|');
        return {std::stof(elements[0]), std::stof(elements[1]), std::stof(elements[2]), std::stof(elements[3])};
    }

    ImVec4 get_val()
    {
        return this->from_string(this->value);
    }

    void draw() override
    {
        ImVec4 vec = this->from_string(this->value);
        imgui_addons::colorpicker(this->imgui_name, &vec);
        this->value = this->to_string(vec);
    }
};
