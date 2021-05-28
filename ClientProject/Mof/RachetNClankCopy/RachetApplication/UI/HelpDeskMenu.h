#ifndef MY_HELP_DESK_MENU_H
#define MY_HELP_DESK_MENU_H


#include "My/UI/UIItem.h"
#include "My/UI/UIPanel.h"

#include <optional>
#include <memory>
#include <unordered_map>

#include "My/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/HelpDesk.h"


namespace my {
/*
class QuickChangeMenuItem : public my::UIItem {
    using super = my::UIItem;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenuItem(const char* name);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="rect"></param>
    void SetRectangle(Mof::CRectangle rect);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
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
*/
class HelpDeskMenu : public my::UIPanel, public my::Observer<const my::HelpDesk::Info&> {
    using super = my::UIPanel;
private:
    //! �\������
    my::HelpDesk::Info _infomation;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    HelpDeskMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const my::HelpDesk::Info& info);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);    
    /// <summary>
    /// �`��
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
#endif // !MY_HELP_DESK_MENU_H