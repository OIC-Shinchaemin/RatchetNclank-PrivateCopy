#pragma once

#include "Singleton.h"
#include "ActionBase.h"
#include <unordered_map>
#include <memory>

// ********************************************************************************
/// <summary>
/// 各アクションの管理クラス
/// </summary>
// ********************************************************************************
class ActionManager : public Singleton<ActionManager> {
private:
    
    //! アクションマップ
    std::unordered_map<std::string, std::shared_ptr<ActionBase>> _action_map;

public:

    // ********************************************************************************
    /// <summary>
    /// コンストラクタ、ここで各アクションを登録している
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    ActionManager(void);

    // ********************************************************************************
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    ~ActionManager(void);

    // ********************************************************************************
    /// <summary>
    /// アクションの呼び出し
    /// </summary>
    /// <param name="key">呼び出すアクション</param>
    /// <returns>true : 成功, false : 失敗</returns>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    bool Action(const std::string& key, std::any any);
};