#ifndef MY_MONEY_MENU_H
#define MY_MONEY_MENU_H


#include "My/UI/UIItem.h"
#include "My/UI/UIPanel.h"

#include <memory>

#include "My/Core/Observer.h"
#include "MY/UI/UICanvas.h"


namespace my {
class MoneyMenu : public my::UIPanel, public my::Observer<int> {
    using super = my::UIPanel;
private:
    //! ����
    int _money;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    MoneyMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="money"></param>
    virtual void OnNotify(int money) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_MONEY_MENU_H