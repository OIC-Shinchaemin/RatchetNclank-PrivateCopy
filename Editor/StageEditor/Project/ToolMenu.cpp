#include "ToolMenu.h"
#include "GuiWindowRect.h"
#include "WindowKeyName.h"
#include "ToolIcon.h"
#include "ParameterMap.h"
#include "EditorParameter.h"
#include "Define.h"

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
        
        bool mode_eye = ((*edit_mode) & EditMode::EditEye);
        void* icon = ToolIcon::GetInstance().GetTexture((mode_eye ? ToolIcon::Eye : ToolIcon::Hand));
        if (ImGui::ImageButton(
            icon,
            size, uv1, uv2, frame_padding,
            (((*edit_mode) & EditMode::EditHand || mode_eye) ? bg_select_col : bg_col))) {
            if (!mode_eye) {
                *edit_mode = EditMode::EditHand | EditMode::MoveCamera;
            }
            else {
                *edit_mode = EditMode::EditEye | EditMode::MoveCamera;
            }
        } ImGui::SameLine();
        
        if (ImGui::ImageButton(ToolIcon::GetInstance().GetTexture(ToolIcon::ArrowMove),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) & EditMode::EditTrans) ? bg_select_col : bg_col))) {
            *edit_mode = EditMode::EditTrans | EditMode::MoveCamera;
        } ImGui::SameLine();

        if (ImGui::ImageButton(ToolIcon::GetInstance().GetTexture(ToolIcon::ArrowRotate),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) & EditMode::EditRotate) ? bg_select_col : bg_col))) {
            *edit_mode = EditMode::EditRotate | EditMode::MoveCamera;
        } ImGui::SameLine();
        if (ImGui::ImageButton(ToolIcon::GetInstance().GetTexture(ToolIcon::ArrowScale),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) & EditMode::EditScale) ? bg_select_col : bg_col))) {
            *edit_mode = EditMode::EditScale | EditMode::MoveCamera;
        } ImGui::SameLine();

        ImGui::Text("    "); ImGui::SameLine();
        if (ImGui::ImageButton(ToolIcon::GetInstance().GetTexture(ToolIcon::Installation),
            size, uv1, uv2, frame_padding,
            (((*edit_mode) & EditMode::InstObject) ? bg_select_col : bg_col))) {
            *edit_mode = EditMode::InstObject;
        } ImGui::SameLine();
    }
    ImGui::GetStyle().WindowPadding = def_window_padding;
    ImGui::GetStyle().ItemSpacing   = def_item_spacing;
    ImGui::End();
}
