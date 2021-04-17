#include "DebugGui.h"
#include "Define.h"
#include "ParameterMap.h"
#include "GuiWindowRect.h"
#include "WindowKeyName.h"

// ********************************************************************************
/// <summary>
/// IsItem系情報
/// </summary>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void DebugGui::ShowIsItemInfoWindow(void) {
    ImGui::Begin("IsItemInfo", ParameterMap<bool>::GetInstance().Get(WindowKeyName::DebugIsItemInfo)); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::DebugIsItemInfo);
        ImGui::Text("IsItemActive               : %s", ImGui::IsItemActive()               ? "TRUE" : "FALSE");
        ImGui::Text("IsItemHovered              : %s", ImGui::IsItemHovered()              ? "TRUE" : "FALSE");
        ImGui::Text("IsItemFocused              : %s", ImGui::IsItemFocused()              ? "TRUE" : "FALSE");
        ImGui::Text("IsItemClicked              : %s", ImGui::IsItemClicked()              ? "TRUE" : "FALSE");
        ImGui::Text("IsItemVisible              : %s", ImGui::IsItemVisible()              ? "TRUE" : "FALSE");
        ImGui::Text("IsItemEdited               : %s", ImGui::IsItemEdited()               ? "TRUE" : "FALSE");
        ImGui::Text("IsItemActivated            : %s", ImGui::IsItemActivated()            ? "TRUE" : "FALSE");
        ImGui::Text("IsItemDeactivated          : %s", ImGui::IsItemDeactivated()          ? "TRUE" : "FALSE");
        ImGui::Text("IsItemDeactivatedAfterEdit : %s", ImGui::IsItemDeactivatedAfterEdit() ? "TRUE" : "FALSE");
        ImGui::Text("IsItemToggledOpen          : %s", ImGui::IsItemToggledOpen()          ? "TRUE" : "FALSE");
        ImGui::Text("IsAnyItemHovered           : %s", ImGui::IsAnyItemHovered()           ? "TRUE" : "FALSE");
        ImGui::Text("IsAnyItemActive            : %s", ImGui::IsAnyItemActive()            ? "TRUE" : "FALSE");
        ImGui::Text("IsAnyItemFocused           : %s", ImGui::IsAnyItemFocused()           ? "TRUE" : "FALSE");
    }
    ImGui::End();
}

// ********************************************************************************
/// <summary>
/// マウス情報
/// </summary>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void DebugGui::ShowMouseInfoWindow(void) {
    // マウス関連
    ImGui::Begin("MouseInfo", ParameterMap<bool>::GetInstance().Get(WindowKeyName::DebugMouseInfo)); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::DebugMouseInfo);
        Vector3 mouse_move;
        Vector2 mouse_pos;
        float   mouse_wheel;
        g_pInput->GetMouseMove(mouse_move);
        g_pInput->GetMousePos(mouse_pos);
        mouse_wheel = g_pInput->GetMouseWheelMove();
        ImGui::Text("mouse move : ");
        ImGui::Text("\tx : %010.6f", mouse_move.x);
        ImGui::Text("\ty : %010.6f", mouse_move.y);
        ImGui::Text("\tz : %010.6f", mouse_move.z);
        ImGui::Text("mouse pos  : ");
        ImGui::Text("\tx : %010.6f", mouse_pos.x);
        ImGui::Text("\ty : %010.6f", mouse_pos.y);
        ImGui::Text("mouse wheel: ");
        ImGui::Text("\tw : %010.6f", mouse_wheel);
    }
    ImGui::End();
}

// ********************************************************************************
/// <summary>
/// Rect情報
/// </summary>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void DebugGui::ShowRectInfoWindow(void) {
    ImGui::Begin("RectInfo", ParameterMap<bool>::GetInstance().Get(WindowKeyName::DebugWindowRectInfo)); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::DebugWindowRectInfo);
        for (const auto& it : GuiWindowRect::GetInstance().GetDataArray()) {
            bool* active = it.active_pointer;
            if (active == nullptr || *active == false) {
                continue;
            }
            ImGui::Text("%s : ", it.name.c_str());
            ImGui::Text("\tpos.x : %08.3f, pos.y  : %08.3f", it.rect.Left, it.rect.Top);
            ImGui::Text("\twidth : %08.3f, height : %08.3f", it.rect.GetWidth(), it.rect.GetHeight());
        }
    }
    ImGui::End();
}
