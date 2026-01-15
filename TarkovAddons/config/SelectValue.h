#pragma once
#include <vector>

#include "ConfigValue.h"
#include "../gui/menu/imgui_addons.h"

class SelectValue : public ConfigValue
{
public:
    SelectValue(int initial, const std::vector<const char*>& options, const std::string& n) : ConfigValue(
        this->to_string(initial), n, this->to_string(initial))
    {
        this->options = options;
    }

    std::vector<const char*> options;

    std::string to_string(int v)
    {
        return std::to_string(v);
    }

    static int from_string(std::string string)
    {
        return std::stoi(string);
    }

    std::string selected() const
    {
        return std::string(this->options[from_string(this->value)]);
    }

    int get_val()
    {
        return this->from_string(this->value);
    }

    void draw() override
    {
        int i = this->from_string(this->value);
        imgui_addons::select(this->imgui_name, &i, this->options);
        this->value = this->to_string(i);
    }
};
