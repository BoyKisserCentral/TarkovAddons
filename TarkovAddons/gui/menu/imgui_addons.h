#pragma once
#include <imgui.h>
#include <imgui_stdlib.h>
#include <string>

#include "menu.h"

namespace imgui_addons
{
    static void centered_text(ImDrawList* draw_list, ImFont* font, float font_size, const ImVec2& pos, const ImVec4 col,
                              const std::string& text)
    {
        const ImVec2 size = ImGui::CalcTextSize(text.c_str());
        draw_list->AddText(font, font_size, {pos.x - size.x / 2, pos.y - size.y / 2}, ImGui::GetColorU32(col),
                           text.c_str());
    }

    static void centered_text(ImDrawList* draw_list, const ImVec2& pos, const ImVec4 col, const std::string& text)
    {
        const ImVec2 size = ImGui::CalcTextSize(text.c_str());
        draw_list->AddText({pos.x - size.x / 2, pos.y - size.y / 2}, ImGui::GetColorU32(col), text.c_str());
    }

    static void tab(const std::string& label, const bool selected, const std::function<void()>& action)
    {
        if (selected) ImGui::PushStyleColor(ImGuiCol_Tab, ImGui::GetStyle().Colors[ImGuiCol_TabActive]);
        if (ImGui::TabItemButton(label.c_str()))
        {
            action();
        }
        if (selected) ImGui::PopStyleColor();
    }

    static bool select(const std::string& label, int* v, const std::vector<const char*>& options)
    {
        ImGui::PushID(label.c_str());
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        std::string just_text = label.substr(0, label.find("##"));
        ImGui::Text(just_text.c_str()); // NOLINT(clang-diagnostic-format-security)

        float width = 200 * menu::get_scale_factor();
        ImGui::SameLine(ImGui::GetWindowWidth() - width - 4 * menu::get_scale_factor());
        ImGui::SetNextItemWidth(width);
        auto res = ImGui::Combo(std::string("##" + label).c_str(), v, options.data(),
                                static_cast<int32_t>(options.size()));

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        ImGui::PopID();

        return res;
    }

    static bool slider_float(const std::string& label, float* v, float min, float max)
    {
        ImGui::PushID(label.c_str());
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        std::string just_text = label.substr(0, label.find("##"));
        ImGui::Text(just_text.c_str()); // NOLINT(clang-diagnostic-format-security)

        float width = 200 * menu::get_scale_factor();
        ImGui::SameLine(ImGui::GetWindowWidth() - width - 4 * menu::get_scale_factor());
        ImGui::SetNextItemWidth(width);
        auto res = ImGui::SliderFloat(std::string("##" + label).c_str(), v, min, max);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        ImGui::PopID();

        return res;
    }

    static bool slider_int(const std::string& label, int* v, int min, int max)
    {
        ImGui::PushID(label.c_str());
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        std::string just_text = label.substr(0, label.find("##"));
        ImGui::Text(just_text.c_str()); // NOLINT(clang-diagnostic-format-security)

        float width = 200 * menu::get_scale_factor();
        ImGui::SameLine(ImGui::GetWindowWidth() - width - 4 * menu::get_scale_factor());
        ImGui::SetNextItemWidth(width);
        auto res = ImGui::SliderInt(std::string("##" + label).c_str(), v, min, max);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        ImGui::PopID();

        return res;
    }

    static bool colorpicker(const std::string& label, ImVec4* v)
    {
        ImGui::PushID(label.c_str());
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        std::string just_text = label.substr(0, label.find("##"));
        ImGui::Text(just_text.c_str()); // NOLINT(clang-diagnostic-format-security)

        float width = 200 * menu::get_scale_factor();
        ImGui::SameLine(ImGui::GetWindowWidth() - width - 4 * menu::get_scale_factor());
        ImGui::SetNextItemWidth(width);
        auto res = ImGui::ColorEdit4(std::string("##" + label).c_str(), reinterpret_cast<float*>(v),
                                     ImGuiColorEditFlags_PickerHueWheel);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        ImGui::PopID();

        return res;
    }

    static bool textbox(const std::string& label, std::string* v)
    {
        ImGui::PushID(label.c_str());
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        std::string just_text = label.substr(0, label.find("##"));
        ImGui::Text(just_text.c_str()); // NOLINT(clang-diagnostic-format-security)

        float width = 200 * menu::get_scale_factor();
        ImGui::SameLine(ImGui::GetWindowWidth() - width - 4 * menu::get_scale_factor());
        ImGui::SetNextItemWidth(width);
        auto res = ImGui::InputText(std::string("##" + label).c_str(), v);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        ImGui::PopID();

        return res;
    }

    static bool checkbox(const std::string& label, bool* v)
    {
        ImGui::PushID(label.c_str());
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        std::string just_text = label.substr(0, label.find("##"));
        ImGui::Text(just_text.c_str()); // NOLINT(clang-diagnostic-format-security)
        std::string state_text = *v ? "ENABLED" : "DISABLED";
        ImVec2 text_rect = ImGui::CalcTextSize(state_text.c_str());
        ImGui::SameLine(ImGui::GetWindowWidth() - text_rect.x - 4 * menu::get_scale_factor());
        ImVec2 p = ImGui::GetCursorScreenPos();

        auto color_hovered = ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_TabActive]);
        auto color_inactive = ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_TabHovered]);
        auto color_active_hovered_t = ImGui::GetStyle().Colors[ImGuiCol_CheckMark];
        color_active_hovered_t.x += 0.15f;
        color_active_hovered_t.y += 0.15f;
        color_active_hovered_t.z += 0.15f;
        auto color_active_hovered = ImGui::GetColorU32(color_active_hovered_t);
        auto color_active = ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_CheckMark]);

        ImGui::InvisibleButton(label.c_str(), text_rect);
        bool hovered = ImGui::IsItemHovered();

        bool clicked = ImGui::IsItemClicked();
        if (clicked)
            *v = !(*v);

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddText(
            p, !*v ? (hovered ? color_active_hovered : color_active) : (hovered ? color_hovered : color_inactive),
            state_text.c_str()
        );

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().FramePadding.y * 2 * menu::get_scale_factor());
        ImGui::PopID();

        return clicked;
    }
};
