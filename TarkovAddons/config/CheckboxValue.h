#pragma once
#include <imgui.h>
#include <sstream>

#include "ConfigValue.h"
#include "../gui/menu/imgui_addons.h"

class CheckboxValue : public ConfigValue
{
public:
    CheckboxValue(bool initial, const std::string& n) : ConfigValue(this->to_string(initial), n,
                                                                    this->to_string(initial))
    {
    }

    std::string to_string(bool v)
    {
        std::ostringstream os("");
        os << std::boolalpha << v;
        return os.str();
    }

    bool from_string(std::string string)
    {
        bool b1;
        std::istringstream is(string);
        is >> std::boolalpha >> b1;
        return b1;
    }

    bool get_val()
    {
        return this->from_string(this->value);
    }

    void draw() override
    {
        bool b = this->from_string(this->value);
        imgui_addons::checkbox(this->imgui_name, &b);
        this->value = this->to_string(b);
    }
};
