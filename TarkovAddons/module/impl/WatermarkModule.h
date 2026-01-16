#pragma once
#include "../Module.h"
#include "../ModuleCategory.h"
#include "../../config/CheckboxValue.h"
#include "../../config/ColorpickerValue.h"
#include "../../config/TextboxValue.h"
#include "../../util/globals.h"

class WatermarkModule : Module
{
public:
    WatermarkModule() : Module("Watermark", Misc)
    {
    }

    CheckboxValue* enabled = conf(new CheckboxValue(true, "Enabled"));
    TextboxValue* text = conf(new TextboxValue(globals::get_display_title(), "Text"));
    ColorpickerValue* color = conf(new ColorpickerValue({0, 0.5, 1, 1}, "Color"));

    void draw_overlay(ImDrawList* draw_list) override
    {
        if (enabled->get_value())
            draw_list->AddText({10, 10}, ImGui::GetColorU32(color->get_value()), text->get().c_str());
    }

    void init() override
    {
    }
};
