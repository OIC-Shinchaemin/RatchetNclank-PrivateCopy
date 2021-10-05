#ifndef RATCHET_UI_GAME_MONEY_MENU_H
#define RATCHET_UI_GAME_MONEY_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/GameMoney.h"
#include "Base/Core/Timer.h"


namespace ratchet ::ui {
class GameMoneyMenu : public base::ui::UIPanel,
    public ratchet::game::gamesystem::GameMoneyMessageListener {
    using super = base::ui::UIPanel;
private:
    //! ����
    int _money;
    //! ����
    int _money_max;
    //! �\��
    bool _show;
    //! ����
    float _time_max;
    //! ��\���^�C�}�[
    base::core::Timer _hide_timer;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    GameMoneyMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="money"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::GameMoneyMessage& message) override;
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
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_GAME_MONEY_MENU_H