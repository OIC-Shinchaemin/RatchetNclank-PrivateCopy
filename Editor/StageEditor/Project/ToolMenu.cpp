#include "ToolMenu.h"
#include "GuiWindowRect.h"
#include "WindowKeyName.h"
#include "ToolIcon.h"
#include "ParameterMap.h"
#include "EditorParameter.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>‚¢‚Ì‚¤‚¦,2021/03/20</created>
/// <changed>‚¢‚Ì‚¤‚¦,2021/03/20</changed>
// ********************************************************************************
void ToolMenu::Show(void) {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

    CRectangle* main_menu_rect = GuiWindowRect::GetInstance().Find(WindowKeyName::MainMenu);
    ImGui::SetNextWindowPos(ImVec2(0, main_menu_rect->Bottom));
    ImGui::SetNextWindowSize(ImVec2(main_menu_rect->GetWidth(), 20));
    ImGui::SetNextWindowBgAlpha(1);
    const ImVec2 def_window_padding = ImGui::GetStyle().WindowPadding;
    const ImVec2 def_item_spacing   = ImGui::GetStyle().ItemSpacing;
    ImGui::GetStyle().WindowPadding = ImVec2(2, 2);
    ImGui::GetStyle().ItemSpacing   = ImVec2(2, 2);
    ImGui::Begin("tool menu", 0, window_flags); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::ToolMenu);
        const ImVec2 size(28, 28);
        const ImVec2 uv1(0, 0);
        const ImVec2 uv2(1, 1);
        const int    frame_padding = 0;
        const ImVec4 bg_select_col(1, 1, 1, 1);
        const ImVec4 bg_col(0, 0, 0, 0);
        const ImVec4 tint_col(1, 1, 1, 1);
        ImGui::Text(""); ImGui::SameLine();
        int* edit_mode = ParameterMap<int>::GetInstance().Get("edit_mode");
        
        if (ImGui::ImageButton(
            ToolIcon::GetInstance().GetTexture(ToolIcon::Hand),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) == 0) ? bg_select_col : bg_col))) {
            *edit_mode = 0;
        } ImGui::SameLine();
        
        if (ImGui::ImageButton(ToolIcon::GetInstance().GetTexture(ToolIcon::ArrowMove),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) == 1) ? bg_select_col : bg_col))) {
            *edit_mode = 1;
        } ImGui::SameLine();

        if (ImGui::ImageButton(ToolIcon::GetInstance().GetTexture(ToolIcon::ArrowRotate),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) == 2) ? bg_select_col : bg_col))) {
            *edit_mode = 2;
        } ImGui::SameLine();
        if (ImGui::ImageButton(ToolIcon::GetInstance().GetTexture(ToolIcon::ArrowScale),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) == 3) ? bg_select_col : bg_col))) {
            *edit_mode = 3;
        } ImGui::SameLine();
    }
    ImGui::GetStyle().WindowPadding = def_window_padding;
    ImGui::GetStyle().ItemSpacing   = def_item_spacing;
    ImGui::End();
}
