#include "ToolMenu.h"
#include "GuiWindowRect.h"
#include "WindowKeyName.h"

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
    ImGui::Begin("tool menu", 0, window_flags); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::ToolMenu);
    }
    ImGui::End();
}
