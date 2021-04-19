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
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenuItem(const char* name);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
class QuickChangeMenu : public my::UIPanel, public my::Observer<Mof::CVector4> {
    using super = my::UIPanel;
private:
    //! 通知用
    my::Observable<std::string> _weapon;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="color"></param>
    virtual void OnNotify(Mof::CVector4 color) override;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddWeaponObserver(const std::shared_ptr<my::Observer<std::string>>& ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_QUICK_CHANGE_MENU_H