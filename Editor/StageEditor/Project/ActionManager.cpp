#include "ActionManager.h"
#include "ActionKeyName.h"

#include "MeshLoad.h"
#include "MeshLoadDialog.h"
#include "SaveProject.h"
#include "LoadProject.h"
#include "ProjectDataPurse.h"
#include "AddObject.h"

// ********************************************************************************
/// <summary>
/// コンストラクタ、ここで各アクションを登録している
/// </summary>
/// <created>いのうえ,2021/03/18</created>
/// <changed>いのうえ,2021/03/18</changed>
// ********************************************************************************
ActionManager::ActionManager(void) {
    _action_map[ActionKeyName::MeshLoad]         = std::make_shared<MeshLoad>();
    _action_map[ActionKeyName::MeshLoadDialog]   = std::make_shared<MeshLoadDialog>();
    _action_map[ActionKeyName::SaveProject]      = std::make_shared<SaveProject>();
    _action_map[ActionKeyName::LoadProject]      = std::make_shared<LoadProject>();
    _action_map[ActionKeyName::ProjectDataPurse] = std::make_shared<ProjectDataPurse>();
    _action_map[ActionKeyName::AddObject]        = std::make_shared<AddObject>();
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
