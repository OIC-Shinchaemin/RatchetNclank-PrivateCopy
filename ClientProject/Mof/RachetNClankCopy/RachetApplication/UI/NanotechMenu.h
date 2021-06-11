#ifndef RACHET_NANOTECH_MENU_H
#define RACHET_NANOTECH_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace rachet {
class NanotechMenuItem : public base::ui::UIItem {
    using super = base::ui::UIItem;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    NanotechMenuItem(const char* name);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
class NanotechMenu : public base::ui::UIPanel, public base::core::Observer<int> {
    using super = base::ui::UIPanel;
private:
    //! �ő�l
    int _hp_max;
    //! Hp
    int _hp;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! ���\�[�X
    std::weak_ptr<rachet::ResourceMgr> _resource_manager;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    NanotechMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="hp"></param>
    virtual void OnNotify(int hp) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RACHET_NANOTECH_MENU_H