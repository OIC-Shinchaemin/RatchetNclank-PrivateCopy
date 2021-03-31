#include "ActionManager.h"
#include "ActionKeyName.h"

#include "MeshLoad.h"
#include "MeshLoadDialog.h"
#include "SaveProject.h"
#include "SaveProjectDialog.h"
#include "LoadProject.h"
#include "LoadProjectDialog.h"
#include "ProjectDataParse.h"
#include "AddObject.h"
#include "FileClose.h"

// ********************************************************************************
/// <summary>
/// コンストラクタ、ここで各アクションを登録している
/// </summary>
/// <created>いのうえ,2021/03/18</created>
/// <changed>いのうえ,2021/03/18</changed>
// ********************************************************************************
ActionManager::ActionManager(void) {
    _action_map[ActionKeyName::MeshLoad]          = std::make_shared<MeshLoad>();
    _action_map[ActionKeyName::MeshLoadDialog]    = std::make_shared<MeshLoadDialog>();
    _action_map[ActionKeyName::SaveProject]       = std::make_shared<SaveProject>();
    _action_map[ActionKeyName::SaveProjectDialog] = std::make_shared<SaveProjectDialog>();
    _action_map[ActionKeyName::LoadProject]       = std::make_shared<LoadProject>();
    _action_map[ActionKeyName::LoadProjectDialog] = std::make_shared<LoadProjectDialog>();
    _action_map[ActionKeyName::ProjectDataParse]  = std::make_shared<ProjectDataParse>();
    _action_map[ActionKeyName::AddObject]         = std::make_shared<AddObject>();
    _action_map[ActionKeyName::FileClose]         = std::make_shared<FileClose>();
}

// ********************************************************************************
/// <summary>
/// デストラクタ
/// </summary>
/// <created>いのうえ,2021/03/18</created>
/// <changed>いのうえ,2021/03/18</changed>
// ********************************************************************************
ActionManager::~ActionManager(void) {
}

// ********************************************************************************
/// <summary>
/// アクションの呼び出し
/// </summary>
/// <param name="key">呼び出すアクション</param>
/// <returns>true : 成功, false : 失敗</returns>
/// <created>いのうえ,2021/03/18</created>
/// <changed>いのうえ,2021/03/18</changed>
// ********************************************************************************
bool ActionManager::Action(const std::string& key, std::any any) {
    // キーからアクションを検索して、見つからなければfalseを返す。
    auto& action = _action_map.find(key);
    if (action == _action_map.end()) {
        return false;
    }
    // 見つければアクション結果を返す。
    return action->second->Action(any);
}
