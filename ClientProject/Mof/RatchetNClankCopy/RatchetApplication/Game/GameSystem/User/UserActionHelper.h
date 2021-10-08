#ifndef RATCHET_GAME_GAME_SYSTEM_USER_USER_ACTION_HELPER_H
#define RATCHET_GAME_GAME_SYSTEM_USER_USER_ACTION_HELPER_H


#include "../../GameSystem/GameSystem.h"

#include <string>

#include "../../../Actor/Character/CharacterDefine.h"
#include "../../../UI/UICreator.h"

namespace ratchet::ui { class UserActionHelperMenu; }
namespace ratchet::game::gamesystem::user {
class UserActionHelper :
    //public std::enable_shared_from_this<UserActionHelper>,
    public game::gamesystem::GameSystem,
    public actor::character::CharacterTalkableMessageListener {
    using super = game::gamesystem::GameSystem;
private:
    //! UI地蔵
    std::unique_ptr<ratchet::ui::UICreator<ratchet::ui::UserActionHelperMenu> >_ui_creator;
    //! リソース
    std::weak_ptr<ratchet::ui::UserActionHelperMenu> _ui;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    UserActionHelper();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~UserActionHelper();
    /// <summary>
    /// 通知イベント
    /// </summary>
    virtual void OnNotify(const actor::character::CharacterTalkableMessage& message);
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name=""></param>
    bool RegisterUI(void);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    bool DisposeUI(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_USER_USER_ACTION_HELPER_H