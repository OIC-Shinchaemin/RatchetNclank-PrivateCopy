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
/// <created>いのうえ,2021/03/30</created>
/// <changed>いのうえ,2021/03/30</changed>
// ********************************************************************************
bool SaveProjectDialog::Action(std::any any) {
    // ファイルパス
    char path[MAX_PATH];
    // 複数読み込んでいるかどうか(TODO:)
    bool array_flag;
    // ダイアログの開始
    bool open = FileDialog::Open(
        NULL, FileDialog::Mode::Save,
        "マップファイル書き込み",
        "map file(*.json)\0*.json\0all file(*.*)\0*.*\0\0",
        "json",
        path, array_flag
    );

    // オープンに成功していれば登録を行う
    if (open) {
        std::string* open_file     = ParameterMap<std::string>::GetInstance().Get("open_file_name");
        *open_file                 = path;
        // ファイル名
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
