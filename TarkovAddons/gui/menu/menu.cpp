#include "menu.h"

#include "resources.h"
#include "../../util/globals.h"
#include "../../util/utils.h"

namespace menu
{
    namespace
    {
        bool draw_imgui = false;
        float scale_factor;
        float font_size;
        float large_font_size;
        ImFont* poppins_regular;
        ImFont* poppins_regular_hud;
        ImFont* sfui_light;
        ImFont* sfui_bold;
        ImFont* icons;
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
        scale_factor = (static_cast<float>(horizontal) / 1920.0f + static_cast<float>(vertical) / 1080.0f) / 2.0f;
        font_size = 16 * scale_factor;
        large_font_size = 20 * scale_factor;
        poppins_regular = io.Fonts->AddFontFromMemoryCompressedBase85TTF(poppins_regular_data, font_size);
        poppins_regular_hud = io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            poppins_regular_data, 256 * scale_factor);
        sfui_light = io.Fonts->AddFontFromMemoryCompressedTTF(light_compressed_data, light_compressed_size,
                                                              font_size);
        sfui_bold = io.Fonts->AddFontFromMemoryCompressedTTF(bold_compressed_data, bold_compressed_size,
                                                             large_font_size);
        icons = io.Fonts->AddFontFromMemoryCompressedTTF(icons_compressed_data, icons_compressed_size,
                                                         font_size);
    }

    void draw()
    {
        theme();
        ImGui::GetMouseCursor();
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        ImGui::GetIO().WantCaptureMouse = is_active();
        if (is_active())
        {
            ImGui::SetNextWindowSize(ImVec2(550, 350), ImGuiCond_Once);
            ImGui::SetNextWindowBgAlpha(1.0f);
            if (ImGui::Begin(globals::get_display_title().c_str(), &draw_imgui,
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                             ImGuiWindowFlags_NoScrollbar))
            {
                ImGui::Button("Test");
            }
            ImGui::End();
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            draw_imgui = !draw_imgui;
        }
    }
}
