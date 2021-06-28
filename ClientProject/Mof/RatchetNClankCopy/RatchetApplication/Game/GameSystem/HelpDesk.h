#ifndef RATCHET_GAME_GAME_SYSTEM_HELP_DESK_H
#define RATCHET_GAME_GAME_SYSTEM_HELP_DESK_H


#include "Base/Core/Observer.h"

#include <memory>
#include <string>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "GameQuest.h"


namespace ratchet {
namespace game {
namespace gamesystem {

class HelpDesk :
    public std::enable_shared_from_this<ratchet::game::gamesystem::HelpDesk>,
    public base::core::Observer<const ratchet::game::gamesystem::GameQuest&> {
public:
    struct Info {
        std::string text;
    };
private:
    //! ���
    Info _info;
    //! ���
    Info _prev_info;
    //! �B������������
    //ratchet::game::gamesystem::GameQuest _current_quest;
    //! �ʒm�p
    base::core::Observable<const ratchet::game::gamesystem::HelpDesk::Info&> _subject;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! �N���A
    bool _completed;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    HelpDesk();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~HelpDesk();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const ratchet::game::gamesystem::GameQuest& quest) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
}
}
#endif // !RATCHET_GAME_GAME_SYSTEM_HELP_DESK_H