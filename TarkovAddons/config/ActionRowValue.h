#pragma once
#include <functional>

#include "CheckboxValue.h"
#include "ConfigValue.h"

class ActionRowValue : public ConfigValue
{
public:
    ActionRowValue(const std::function<void ()>& action, const std::string& n, bool sameline = false) : ConfigValue(
        "", n, "")
    {
        this->action = action;
        this->sameline = sameline;
    }

    std::function<void ()> action;
    bool sameline;

    void draw() override
    {
        if (sameline) ImGui::SameLine();
        if (ImGui::Button(this->imgui_name.c_str()))
        {
            action();
        }
    }
};
