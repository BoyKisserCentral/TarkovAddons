#include "menu.h"

#include "resources.h"
#include "../../module/ModuleManager.h"
#include "../../util/globals.h"
#include "../../util/utils.h"

namespace menu
{
    namespace
    {
        bool draw_imgui = false;
        float widthh;
        float heightt;
        float scale_factor;
        float font_size;
        float large_font_size;
        float hud_font_size;
        ImFont* poppins_regular;
        ImFont* poppins_regular_hud;
        ImFont* sfui_light;
        ImFont* sfui_bold;
        ImFont* icons;

        ModuleCategory selected_tab = Aimbot;
    }

    float get_hud_font_size()
    {
        return hud_font_size;
    }

    ImFont* get_hud_font()
    {
        return poppins_regular_hud;
    }

    float get_scale_factor()
    {
        return scale_factor;
    }

    float get_width()
    {
        return widthh;
    }

    float get_height()
    {
        return heightt;
    }

    bool is_active()
    {
        return draw_imgui == true;
    }

    void setup()
    {
        ImGuiIO io = ImGui::GetIO();
        int horizontal = 0;
        int vertical = 0;
        utils::get_desktop_resolution(horizontal, vertical);
        widthh = static_cast<float>(horizontal);
        heightt = static_cast<float>(vertical);
        scale_factor = (static_cast<float>(horizontal) / 1920.0f + static_cast<float>(vertical) / 1080.0f) / 2.0f;
        font_size = 16 * scale_factor;
        large_font_size = 18 * scale_factor;
        hud_font_size = 256 * scale_factor;
        poppins_regular = io.Fonts->AddFontFromMemoryCompressedBase85TTF(poppins_regular_data, font_size);
        poppins_regular_hud = io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            poppins_regular_data, hud_font_size);
        sfui_light = io.Fonts->AddFontFromMemoryCompressedTTF(light_compressed_data, light_compressed_size,
                                                              font_size);
        sfui_bold = io.Fonts->AddFontFromMemoryCompressedTTF(bold_compressed_data, bold_compressed_size,
                                                             large_font_size);
        icons = io.Fonts->AddFontFromMemoryCompressedTTF(icons_compressed_data, icons_compressed_size,
                                                         font_size);
    }

    void draw()
    {
        // draw menu
        theme();
        ImGui::StyleColorsClassic();
        ImGui::GetMouseCursor();
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        ImGui::GetIO().WantCaptureMouse = is_active();
        if (is_active())
        {
            constexpr float width = 700;
            constexpr float height = 400;
            ImGui::SetNextWindowSize(ImVec2(width * scale_factor, height * scale_factor), ImGuiCond_Once);
            ImGui::SetNextWindowBgAlpha(1.0f);
            if (ImGui::Begin(globals::get_display_title().c_str(), &draw_imgui,
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                             ImGuiWindowFlags_NoScrollbar))
            {
                // tab selection
                ImGui::BeginTabBar("");
                imgui_addons::tab("Aimbot", selected_tab == Aimbot, []
                {
                    selected_tab = Aimbot;
                });
                imgui_addons::tab("Visuals", selected_tab == Visuals, []
                {
                    selected_tab = Visuals;
                });
                imgui_addons::tab("Exploit", selected_tab == Exploit, []
                {
                    selected_tab = Exploit;
                });
                imgui_addons::tab("Misc", selected_tab == Misc, []
                {
                    selected_tab = Misc;
                });
                imgui_addons::tab("Config", selected_tab == Config, []
                {
                    selected_tab = Config;
                });
                ImGui::EndTabBar();

                bool overflow = false;
                ImVec2 window_pos = ImGui::GetWindowPos();
                ImVec2 window_size = ImGui::GetWindowSize();
                float window_min = window_pos.x + ImGui::GetCursorPosX();
                float window_max = window_pos.x + window_size.x;
                float window_space = window_max - window_min;
                ImGui::BeginChild("##Child1", {0.5f * window_space - 4 * scale_factor, 0});
                ModuleManager::get_instance()->apply([window_space, height, &overflow](Module* m)
                {
                    if (m->category != selected_tab) return;
                    ImGui::Dummy({0, 3 * scale_factor});
                    ImGui::Indent();
                    ImGui::PushFont(sfui_bold);
                    ImGui::Text(m->name.c_str());
                    ImGui::Dummy({0, 4 * scale_factor});
                    ImGui::PopFont();
                    ImGui::Unindent();
                    m->apply([](ConfigValue* c)
                    {
                        ImGui::Indent();
                        c->draw();
                        ImGui::Unindent();
                    });

                    if (ImGui::GetCursorPosY() >= 0.5f * height * scale_factor)
                    {
                        overflow = true;
                        ImGui::EndChild();
                        ImGui::SameLine();
                        ImGui::BeginChild("##Child2", {0.5f * window_space - 4 * scale_factor, 0});
                    }
                });
                if (!overflow)
                {
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild("##Child2", {0.5f * window_space - 4 * scale_factor, 0});
                }
                ImGui::EndChild();
            }
            ImGui::End();
        }

        // listen to menu key
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            draw_imgui = !draw_imgui;
        }

        // draw overlay
        auto draw_list = ImGui::GetBackgroundDrawList();
        ModuleManager::get_instance()->apply([draw_list](Module* m)
        {
            m->draw_overlay(draw_list);
        });
    }
}
