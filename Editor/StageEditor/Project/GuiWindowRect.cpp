#include "GuiWindowRect.h"
#include "ParameterMap.h"

// ********************************************************************************
/// <summary>
/// ��`�̓o�^
/// </summary>
/// <param name="name">�o�^��</param>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void GuiWindowRect::Add(const std::string& name) {
    LPRectangle rect_pointer = Find(name);
    Data        data;
    ImVec2      pos     = ImGui::GetWindowPos();
    ImVec2      size    = ImGui::GetWindowSize();
    CRectangle  rect    = CRectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
    data.name           = name;
    data.rect           = rect;
    data.active_pointer = ParameterMap<bool>::GetInstance().Get(name);
    if (rect_pointer != nullptr) {
        *rect_pointer = rect;
    }
    else {
        _data_array.push_back(data);
    }
}

// ********************************************************************************
/// <summary>
/// ��`�̌���
/// </summary>
/// <param name="name">�������閼�O</param>
/// <returns>�����F��`�f�[�^�|�C���^�A���s�Fnullptr</returns>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
CRectangle* GuiWindowRect::Find(const std::string& name) {
    auto& data = std::find_if(_data_array.begin(), _data_array.end(),
        [&](const Data& data) { return (data.name == name); });
    if (data != _data_array.end()) {
        return &(data->rect);
    }
    return nullptr;
}

// ********************************************************************************
/// <summary>
/// �f�[�^�z��̎擾
/// </summary>
/// <returns>�f�[�^�z��</returns>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
const std::vector<GuiWindowRect::Data>& GuiWindowRect::GetDataArray(void) const {
    return _data_array;
}

// ********************************************************************************
/// <summary>
/// Gui�𑀍삵�Ă��邩�̃t���O�擾
/// </summary>
/// <returns>Gui�𑀍삵�Ă��邩�̃t���O</returns>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
bool GuiWindowRect::IsGuiItemUse(void) const {

    bool    over_guirect = false;
    Vector2 mouse_pos;
    g_pInput->GetMousePos(mouse_pos);
    for (const auto& it : _data_array) {
        const bool* show_pointer = (it.active_pointer);
        if (show_pointer == nullptr || *show_pointer == false) {
            continue;
        }
        if (it.rect.CollisionPoint(mouse_pos)) {
            over_guirect = true;
            break;
        }
    }

    bool is_item_active                 = ImGui::IsItemActive();
    bool is_item_hovered                = ImGui::IsItemHovered();
    bool is_item_focused                = ImGui::IsItemFocused();
    bool is_item_clicked                = ImGui::IsItemClicked();
    bool is_item_edited                 = ImGui::IsItemEdited();
    bool is_item_activated              = ImGui::IsItemActivated();
    bool is_item_deactivated            = ImGui::IsItemDeactivated();
    bool is_item_deactivated_after_edit = ImGui::IsItemDeactivatedAfterEdit();
    bool is_item_toggled_open           = ImGui::IsItemToggledOpen();
    bool is_any_item_hovered            = ImGui::IsAnyItemHovered();
    bool is_any_item_active             = ImGui::IsAnyItemActive();
    bool is_any_item_ficysed            = ImGui::IsAnyItemFocused();

    return (
        over_guirect || is_item_active || is_item_hovered || is_item_focused ||
        is_item_clicked || is_item_edited || is_item_activated || 
        is_item_deactivated || is_item_deactivated_after_edit ||
        is_item_toggled_open || is_any_item_hovered || is_any_item_active ||
        is_any_item_ficysed
        );
}
