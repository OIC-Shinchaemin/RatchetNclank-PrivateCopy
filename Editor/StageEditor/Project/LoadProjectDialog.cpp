#include "LoadProjectDialog.h"
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
bool LoadProjectDialog::Action(std::any any) {

    // ファイルパス
    char path[MAX_PATH];
    // 複数読み込んでいるかどうか(TODO:)
    bool array_flag;
    // ダイアログの開始
    bool open = FileDialog::Open(
        NULL, FileDialog::Mode::Open,
        "マップファイル読み込み",
        "map file(*.json)\0*.json\0all file(*.*)\0*.*\0\0",
        "json",
        path, array_flag
    );

    if (open) {
        std::string* resource_path = ParameterMap<std::string>::GetInstance().Get("resource_path");
        std::string* open_file     = ParameterMap<std::string>::GetInstance().Get("open_file_name");
        *open_file = path;
        // ファイル名
        std::string* out       = std::any_cast<std::string*>(any);
        std::string  file_name = FileDialog::GetFileName(path) + FileDialog::GetExt(path);
        *out = FileDialog::ChangeRelativePath(path, resource_path->c_str());
        rapidjson::Document document;
        LoadData data(*out, &document);
        if (ActionManager::GetInstance().Action(ActionKeyName::LoadProject, &data)) {
            ParseData save_data;
            std::get<0>(save_data) = &document;
            std::get<1>(save_data) = ParameterMap<MeshList>::GetInstance().Get("mesh_list");
            std::get<2>(save_data) = ParameterMap<ObjectList>::GetInstance().Get("object_list");
            return (ActionManager::GetInstance().Action(ActionKeyName::ProjectDataParse, &save_data));
        }
    }
    return false;
}
