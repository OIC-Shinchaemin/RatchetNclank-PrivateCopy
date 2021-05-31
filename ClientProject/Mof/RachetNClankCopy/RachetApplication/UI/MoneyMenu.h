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
    //! お金
    int _money;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    MoneyMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="money"></param>
    virtual void OnNotify(int money) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_MONEY_MENU_H