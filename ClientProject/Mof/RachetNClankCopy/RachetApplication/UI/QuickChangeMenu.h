#ifndef MY_QUICK_CHANGE_MENU_H
#define MY_QUICK_CHANGE_MENU_H


#include "My/UI/UIPanel.h"

#include "My/Core/Observable.h"
#include "../Game/GameSystem/QuickChangeSystem.h"


namespace my {
class QuickChangeMenuItem : public my::UIItem {
    using super = my::UIItem;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenuItem(const char* name);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
class QuickChangeMenu : public my::UIPanel, public my::Observer<Mof::CVector4> {
    using super = my::UIPanel;
private:
    //! �ʒm�p
    my::Observable<std::string> _weapon;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="color"></param>
    virtual void OnNotify(Mof::CVector4 color) override;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddWeaponObserver(const std::shared_ptr<my::Observer<std::string>>& ptr);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_QUICK_CHANGE_MENU_H