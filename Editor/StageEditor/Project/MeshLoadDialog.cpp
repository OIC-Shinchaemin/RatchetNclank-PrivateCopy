#include "MeshLoadDialog.h"
#include "FileDialog.h"
#include "ActionManager.h"
#include "Define.h"
#include "ParameterMap.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>いのうえ,2021/03/18</created>
/// <changed>いのうえ,2021/03/18</changed>
// ********************************************************************************
bool MeshLoadDialog::Action(std::any any) {
    // ファイルパス
    char path[MAX_PATH];
    // 複数読み込んでいるかどうか(TODO:)
    bool array_flag;
    // ダイアログの開始
    bool open = FileDialog::Open(
        NULL, FileDialog::Mode::Open,
        "メッシュファイル読み込み",
        "mesh file(*.mom)\0*.mom\0all file(*.*)\0*.*\0\0",
        "mom",
        path, array_flag
    );

    // オープンに成功していればメッシュの登録を行う
    if (open) {
        std::string* resource_path = ParameterMap<std::string>::GetInstance().Get("resource_path");
        // ファイル名
        std::string* out       = std::any_cast<std::string*>(any);
        std::string  file_name = FileDialog::GetFileName(path) + FileDialog::GetExt(path);
        *out = FileDialog::ChangeRelativePath(path, resource_path->c_str());
        // 登録データの作成
        //std::pair<std::string, std::string> data(*out, path);
        // メッシュの読み込み、登録をする
        //ActionManager::GetInstance().Action("MeshLoad", data);
        return true;
    }
    return false;
}
