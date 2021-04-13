#include "SaveProjectDialog.h"
#include "ActionManager.h"
#include "ActionKeyName.h"
#include "FileDialog.h"
#include "ParameterMap.h"
#include "Define.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>���̂���,2021/03/30</created>
/// <changed>���̂���,2021/03/30</changed>
// ********************************************************************************
bool SaveProjectDialog::Action(std::any any) {
    // �t�@�C���p�X
    char path[MAX_PATH];
    // �����ǂݍ���ł��邩�ǂ���(TODO:)
    bool array_flag;
    // �_�C�A���O�̊J�n
    bool open = FileDialog::Open(
        NULL, FileDialog::Mode::Save,
        "�}�b�v�t�@�C����������",
        "map file(*.json)\0*.json\0all file(*.*)\0*.*\0\0",
        "json",
        path, array_flag
    );

    // �I�[�v���ɐ������Ă���Γo�^���s��
    if (open) {
        std::string* open_file     = ParameterMap<std::string>::GetInstance().Get("open_file_name");
        *open_file                 = path;
        // �t�@�C����
        std::string* out           = std::any_cast<std::string*>(any);
        std::string* resourse_path = ParameterMap<std::string>::GetInstance().Get("resource_path");
        std::string  file_name     = FileDialog::GetFileName(path) + FileDialog::GetExt(path);
        std::string  full_path     = FileDialog::ChangeFullPath(file_name.c_str());
        *out                       = FileDialog::ChangeRelativePath(full_path.c_str(), resourse_path->c_str());
        SaveData save_data;
        std::get<0>(save_data) = *out;
        std::get<1>(save_data) = ParameterMap<MeshList>::GetInstance().Get("mesh_list");
        std::get<2>(save_data) = ParameterMap<ObjectList>::GetInstance().Get("object_list");
        ActionManager::GetInstance().Action(ActionKeyName::SaveProject, &save_data);
        return true;
    }
    return false;
}
