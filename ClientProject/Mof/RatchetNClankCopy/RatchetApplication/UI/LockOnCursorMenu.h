#ifndef RATCHET_UI_LOCK_ON_CURSOR_MENU_H
#define RATCHET_UI_LOCK_ON_CURSOR_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <optional>
#include <memory>

#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace ratchet::ui {
class LockOnCursorMenu : public base::ui::UIPanel, public base::core::Observer<std::optional<Mof::CVector3>> {
    using super = base::ui::UIPanel;
private:
    //! �ʒu
    std::optional<Mof::CVector3> _position;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource_manager;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    LockOnCursorMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="position"></param>
    virtual void OnNotify(std::optional<Mof::CVector3> position) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    //void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_NANOTECH_MENU_H