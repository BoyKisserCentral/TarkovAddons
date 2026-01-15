#pragma once
#include <string>

/**
 * Represents a config value of a module and its imgui representation.
 * 
 * @tparam T Value Type
 */
class ConfigValue
{
public:
    virtual ~ConfigValue() = default;

    ConfigValue(const std::string& initial, const std::string& name, const std::string& def)
    {
        this->value = initial;
        this->default_string = def;
        this->name = name;
    }

    std::string value;
    std::string name;
    std::string module;
    std::string default_string;
    std::string imgui_name;

    /**
     * Register with the module
     * @param mod module name
     */
    void reg(const std::string& mod)
    {
        this->module = mod;
        this->imgui_name = this->name + "##" + this->module;
    }

    virtual void draw() = 0; // NOLINT(portability-template-virtual-member-function)

    void set(const std::string& string)
    {
        this->value = string;
    }

    std::string get()
    {
        return this->value;
    }
};
