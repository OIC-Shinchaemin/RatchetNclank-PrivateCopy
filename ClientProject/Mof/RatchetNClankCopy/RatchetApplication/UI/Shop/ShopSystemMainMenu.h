#ifndef RATCHET_UI_SHOP_SHOP_SYSTEM_MAIN_MENU_H
#define RATCHET_UI_SHOP_SHOP_SYSTEM_MAIN_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "../../Game/GameSystem/ShopSystem.h"


namespace ratchet::ui::shop {
class ShopSystemMainMenu : public base::ui::UIPanel {
    using super = base::ui::UIPanel;
private:
    //! �\��
    bool _show;
    //! ���
    ratchet::game::gamesystem::ShopSystem::Info _infomation;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    ShopSystemMainMenu(const char* name);
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
#endif // RATCHET_UI_SHOP_SHOP_SYSTEM_MAIN_MENU_H