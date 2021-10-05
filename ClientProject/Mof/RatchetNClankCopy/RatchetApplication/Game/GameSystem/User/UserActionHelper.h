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
    //! UI�n��
    ratchet::ui::UICreator<ratchet::ui::UserActionHelperMenu> _ui_creator;
    //! ���\�[�X
    std::weak_ptr<ratchet::ui::UserActionHelperMenu> _ui;
    //! ���\�[�X
    //std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    //std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    UserActionHelper();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~UserActionHelper();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    virtual void OnNotify(const actor::character::CharacterTalkableMessage& message);
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name=""></param>
    bool RegisterUI(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_USER_USER_ACTION_HELPER_H