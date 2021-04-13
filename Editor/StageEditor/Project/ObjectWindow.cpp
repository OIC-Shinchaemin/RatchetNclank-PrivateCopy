#include "ObjectWindow.h"
#include "WindowKeyName.h"
#include "GuiWindowRect.h"
#include "ParameterMap.h"
#include "ActionManager.h"
#include "ActionKeyName.h"
#include "CommandManager.h"
#include "ObjectRemoveCommand.h"

// ********************************************************************************
/// <summary>
/// �I�u�W�F�N�g���X�g�̕\��
/// </summary>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::ShowObjectList(void) {
    int size = _object_list.size();
    int i = 0;
    ImGui::BeginChild("object list", ImVec2(150, -ImGui::GetFrameHeightWithSpacing()), true);
    for (auto& it : _object_list) {
        if (ImGui::Selectable(it.name.c_str(), _object_list_current == i)) {
            _object_list_current = i;
            _object_select_item  = &it;
        }
        i++;
    }
    ImGui::EndChild();
}

// ********************************************************************************
/// <summary>
/// �I�𒆂̃I�u�W�F�N�g�f�[�^����\��
/// </summary>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::ShowObjectInfo(void) {
    ImGui::BeginGroup(); {
        // ���b�V�����֘A�̕\��
        ImGui::BeginChild("object info", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
        // �I�𒆃A�C�e��������ꍇ�̂ݕ\������
        if (_object_select_item) {
            // �ύX�̃`�F�b�N
            bool change[5] = { false, false, false, false, false };
            _object_select_item_prev = *_object_select_item;
            // �t�@�C������\������
            char object_name[128]    =  "";
            int  object_name_length  = 128;
            strcpy(object_name, _object_select_item->name.c_str());
            // ���O�̕\���Ɠ��͂���ύX�ł���悤�ɂ���
            if (ImGui::InputText("object name", object_name, object_name_length, ImGuiInputTextFlags_EnterReturnsTrue)) {
                _object_select_item->name = object_name;
                change[3] = true;
            };
            // �e�X�e�[�^�X���h���b�O�����ړ��͂��邩�ŕҏW�ł���悤�ɂ���
            ImGui::Text("input mode : "); ImGui::SameLine();
            if (ImGui::RadioButton("drag" ,  _object_data_input_mode)) { _object_data_input_mode =  true; } ImGui::SameLine();
            if (ImGui::RadioButton("input", !_object_data_input_mode)) { _object_data_input_mode = false; }
            if (_object_data_input_mode) {
                change[0] = ImGui::DragFloat3("position", _object_select_item->position,           0.01f, MOF_FLOAT_MINF, MOF_FLOAT_INF);
                change[1] = ImGui::DragFloat3("scale"   , _object_select_item->scale   ,           0.01f, MOF_FLOAT_MINF, MOF_FLOAT_INF);
                change[2] = ImGui::DragFloat3("rotation", _object_select_item->rotation, MOF_ToRadian(1), MOF_FLOAT_MINF, MOF_FLOAT_INF);
            }
            else {
                change[0] = ImGui::InputFloat3("position", _object_select_item->position);
                change[1] = ImGui::InputFloat3("scale"   , _object_select_item->scale);
                change[2] = ImGui::InputFloat3("rotation", _object_select_item->rotation);
            }
            // �t�@�C�����̕\��
            _object_select_item = GetSelectObjectData();
            if (_object_select_item) {
                if (_object_select_item->mesh_index >= 0) {
                    const int       mesh_no   = _object_select_item->mesh_index;
                    const MeshList* mesh_list = ParameterMap<MeshList>::GetInstance().Get("mesh_list");
                    const int mesh_size = mesh_list->size();
                    std::string combo_list;
                    for (const auto& it : *mesh_list) {
                        combo_list += (it.first) + '\0';
                    }
                    combo_list += '\0';
                    int prev = _object_select_item->mesh_index;
                    ImGui::Combo("mesh", &_object_select_item->mesh_index, combo_list.c_str());
                    change[4] = (prev != _object_select_item->mesh_index);
                }
                else {
                    ImGui::Text("file : no mesh");
                }
            }
            // �ύX���ꂽ���̊Ď�.����Ă���΃f�[�^��o�^����
            for (auto& it : change) {
                if (it) {
                    _object_change_flag = true;
                    _command_register.SetObjectData(_object_select_item);
                    break;
                }
                _object_change_flag = false;
            }
            // �f�[�^�̔j��
            if (ImGui::Button("remove")) {
                CommandManager::GetInstance().Register(std::make_shared<ObjectRemoveCommand>());
            }
        }
        ImGui::EndChild();
    }
    ImGui::EndGroup();
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
ObjectWindow::ObjectWindow(void) {
    ParameterMap<ObjectList>::GetInstance().Set("object_list", &_object_list);
}

// ********************************************************************************
/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
ObjectWindow::~ObjectWindow(void) {
}

// ********************************************************************************
/// <summary>
/// �E�B���h�E�̕\��
/// </summary>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::Show(void) {
    ImGui::Begin("object window", ParameterMap<bool>::GetInstance().Get(WindowKeyName::ObjectWindow)); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::ObjectWindow);
        // ���X�g�̕\��
        ShowObjectList(); ImGui::SameLine();
        // ���̕\��
        ShowObjectInfo();
    }
    ImGui::End();

    if (_object_select_item) {
        // �R�}���h�p�ێ��ϐ�
        ObjectData tmp       = *_object_select_item;
        *_object_select_item = _object_select_item_prev;
        // �R�}���h�̍X�V
        _command_register.Update();
        *_object_select_item = tmp;
    }

}

// ********************************************************************************
/// <summary>
/// �I�u�W�F�N�g�f�[�^�̒ǉ�
/// </summary>
/// <param name="data">�ǉ�����f�[�^</param>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::Add(ObjectData& data) {
    AddObjectData object_data;
    object_data.first  = &data;
    object_data.second = &_object_list;
    ActionManager::GetInstance().Action(ActionKeyName::AddObject, &object_data);

    _object_list_current = static_cast<int>(_object_list.size() - 1);
    _object_select_item  = &(_object_list[_object_list_current]);
    data = *_object_select_item;
}

// ********************************************************************************
/// <summary>
/// �f�[�^�̔j��
/// </summary>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::Remove(void) {
    Remove(*_object_select_item);
}

// ********************************************************************************
/// <summary>
/// �f�[�^�̔j��
/// </summary>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::Remove(const ObjectData& data) {
    // ���X�g����폜
    _object_list.erase(
        std::find_if(_object_list.begin(), _object_list.end(),
            [&](const ObjectData& data_) { return ObjectData::Compare(data_, data); }
        )
    );
    // �I�𒆂̃f�[�^�������ւ��Ă���
    if (_object_list.size() > 0 && _object_list_current >= 0) {
        _object_list_current = max(0, _object_list_current - 1);
        _object_select_item  = &_object_list[_object_list_current];
    }
    else {
        _object_list_current = 0;
        _object_select_item  = nullptr;
    }
}

// ********************************************************************************
/// <summary>
/// ���ݑI�𒆂̃f�[�^���擾����
/// </summary>
/// <returns>���ݑI�𒆂̃f�[�^�|�C���^</returns>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
ObjectData* ObjectWindow::GetSelectObjectData(void) {
    if (_object_select_item == nullptr && _object_list.size() > 0) {
        _object_select_item = &(_object_list[0]);
    }
    else if (_object_list.size() <= 0) {
        _object_select_item = nullptr;
    }
    return _object_select_item;
}

// ********************************************************************************
/// <summary>
/// �I�u�W�F�N�g���X�g�̎擾
/// </summary>
/// <returns>�I�u�W�F�N�g���X�g</returns>
/// <created>���̂���,2021/03/20</created>
/// <changed>���̂���,2021/03/20</changed>
// ********************************************************************************
const std::vector<ObjectData>& ObjectWindow::GetObjectList(void) const {
    return _object_list;
}
std::vector<ObjectData>& ObjectWindow::GetObjectList(void) {
    return _object_list;
}

// ********************************************************************************
/// <summary>
/// �I�𒆂̃I�u�W�F�N�g�ԍ��̎擾
/// </summary>
/// <returns>�I�𒆂̃I�u�W�F�N�g�ԍ�</returns>
/// <created>���̂���,2021/04/08</created>
/// <changed>���̂���,2021/04/08</changed>
// ********************************************************************************
int ObjectWindow::GetSelectNo(void) const {
    return _object_list_current;
}
