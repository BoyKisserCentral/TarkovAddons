#pragma once
#include "ConfigValue.h"
#include "../gui/menu/imgui_addons.h"

class KeybindValue : public ConfigValue
{
public:
    KeybindValue(const int initial, const std::string& n) : ConfigValue(n)
    {
        this->value_ = initial;
        this->def_ = initial;
    }

    void draw() override
    {
        imgui_addons::keybind(this->get_imgui_title(), &this->value_);
    }

    void set(const std::string& string) override
    {
        this->value_ = from_string(string);
    }

    std::string get() override
    {
        return to_string(this->value_);
    }

    std::string get_default() override
    {
        return to_string(this->def_);
    }

    [[nodiscard]] int get_value() const
    {
        return this->value_;
    }

private:
    int value_;
    int def_;

    static std::string to_string(const int v)
    {
        return std::to_string(v);
    }

    static int from_string(const std::string& string)
    {
        return std::stoi(string);
    }
};
