#include "MeshWindow.h"
#include "ParameterMap.h"
#include "GuiWindowRect.h"
#include "FileDialog.h"
#include "ActionManager.h"
#include "ActionKeyName.h"
#include "WindowKeyName.h"
#include <filesystem>
#include "CommandManager.h"
#include "MeshLoadCommand.h"
#include "MeshRemoveCommand.h"

//! ToDo
//extern CTexture                  mesh_view_target;

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
void MeshWindow::ShowMeshList(void) {
    int size = _mesh_list.size();
    int i    = 0;
    ImGui::BeginChild("mesh list", ImVec2(150, -ImGui::GetFrameHeightWithSpacing()), true);
    for (auto& it : _mesh_list) {
        if (ImGui::Selectable(it.first.c_str(), _mesh_list_current == i)) {
            _mesh_list_current = i;
            _mesh_select_item  = &it;
        }
        i++;
    }
    ImGui::EndChild();
}

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
void MeshWindow::ShowMeshInfo(void) {
    ImGui::BeginGroup(); {
        // ���b�V�����֘A�̕\��
        ImGui::BeginChild("mesh info", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
        _mesh_select_item = GetSelectMeshData();
        // �ǂݍ��݃{�^��
        if (ImGui::Button("load")) {
            MeshLoadDialog();
        } ImGui::SameLine();
        // �폜�{�^��
        if (ImGui::Button("delete") && _mesh_select_item) {
            CommandManager::GetInstance().Register(std::make_shared<MeshRemoveCommand>());
        }
        // �t�@�C������\������
        char* text      = "";
        int text_length =  0;
        if (_mesh_select_item) {
            std::shared_ptr<CMeshContainer> mesh = _mesh_select_item->second.lock();
            text        = mesh->GetName()->GetString();
            text_length = mesh->GetName()->GetLength();
        }
        ImGui::InputTextWithHint("file", "select mesh...", text, text_length, ImGuiInputTextFlags_ReadOnly);
        ImGui::Text(std::filesystem::current_path().string().c_str());
		//! ToDo
        //ImGui::Image((void*)mesh_view_target.GetTexture(), ImVec2(200, 200));
        ImGui::EndChild();
    }
    ImGui::EndGroup();
}

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <returns></returns>
/// <created>���̂���,2021/03/21</created>
/// <changed>���̂���,2021/03/21</changed>
// ********************************************************************************
MeshWindow::MeshWindow(void) {
    ParameterMap<MeshList>::GetInstance().Set("mesh_list", &_mesh_list);
}

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <returns></returns>
/// <created>���̂���,2021/03/21</created>
/// <changed>���̂���,2021/03/21</changed>
// ********************************************************************************
MeshWindow::~MeshWindow(void) {
}

// ********************************************************************************
/// <summary>
/// �E�B���h�E�̕\��
/// </summary>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void MeshWindow::Show(void) {
    ImGui::Begin("MeshWindow", ParameterMap<bool>::GetInstance().Get(WindowKeyName::MeshWindow)); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::MeshWindow);

        // �^�u�@�\�̎g�p
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabItemFlags_None)) {
            // Mesh�֘A�^�u
            if (ImGui::BeginTabItem("Mesh")) {

                // Mesh���X�g�̕\��(��)
                ShowMeshList(); ImGui::SameLine();
                // (�E)
                ShowMeshInfo();

                ImGui::EndTabItem();
            }
            // Terrain�֘A�^�u
            if (ImGui::BeginTabItem("Terrain")) {
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

    }
    ImGui::End();
}

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <returns></returns>
/// <created>���̂���,2021/03/19</created>
/// <changed>���̂���,2021/03/19</changed>
// ********************************************************************************
MeshData* MeshWindow::GetSelectMeshData(void) {
    if (_mesh_select_item == nullptr && _mesh_list.size() > 0) {
        _mesh_select_item = &(_mesh_list[0]);
    }
    else if (_mesh_list.size() <= 0) {
        _mesh_select_item = nullptr;
    }

    return _mesh_select_item;
}

int MeshWindow::GetSelectNo(void) const {
    return _mesh_list_current;
}

void MeshWindow::SetSelectNo(int no) {
    _mesh_list_current = no;
}

const MeshList& MeshWindow::GetMeshList(void) const {
    return _mesh_list;
}

MeshList& MeshWindow::GetMeshList(void) {
    return _mesh_list;
}

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
void MeshWindow::AddMeshList(const MeshData* data) {
    _mesh_list_current = _mesh_list.size();
    _mesh_list.push_back(*data);
    _mesh_select_item  = &(_mesh_list[_mesh_list_current]);
}

void MeshWindow::MeshLoadDialog(void) {
    // �_�C�A���O�Ńt�@�C����ǂݍ���
    std::string filename;
    // �f�[�^�̎Q�ƁA�o�^
    if (ActionManager::GetInstance().Action(ActionKeyName::MeshLoadDialog, &filename)) {
        CommandManager::GetInstance().Register(std::make_shared<MeshLoadCommand>(filename, filename));
        //std::weak_ptr<CMeshContainer> mesh = MeshAsset::GetAsset(filename);
        //MeshLoad(&MeshData(FileDialog::GetFileName(filename.c_str()), mesh));
    }
}

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
void MeshWindow::MeshRelease(void) {
    const std::string key       = MeshAsset::GetKey(_mesh_select_item->second.lock());
    const int         use_count = MeshAsset::GetUseCount(key);

    // �����ȊO�ɂ��Q�Ƃ�����ꍇ�͏����Ȃ�
    if (use_count > 1) {
        MessageBox(
            NULL,
            "�g�p���Ă���I�u�W�F�N�g�����ׂč폜���Ă��������x��������������",
            "���̃��b�V���͎g�p����Ă��܂�",
            MB_OK
        );
        return;
    }
    MeshAsset::Erase(key);
    auto& it = std::find_if(
        _mesh_list.begin(), _mesh_list.end(),
        [=](const MeshData& obj) { return obj.first == _mesh_select_item->first; }
    );

    auto& next = _mesh_list.erase(it);
    if (next == _mesh_list.end()) {
        if (_mesh_list.size() <= 0) {
            _mesh_select_item  = nullptr;
            _mesh_list_current = 0;
        }
        else {
            _mesh_list_current = max(0, _mesh_list_current - 1);
            _mesh_select_item  = &_mesh_list[_mesh_list_current];
        }
    }
    else {
        _mesh_select_item = &_mesh_list[_mesh_list_current];
    }
}