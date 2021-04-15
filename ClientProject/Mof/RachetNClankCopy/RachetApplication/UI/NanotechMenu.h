#ifndef MY_NANOTECH_MENU_H
#define MY_NANOTECH_MENU_H


#include "My/UI/UIPanel.h"

#include "My/Core/Observable.h"
#include "MY/UI/UICanvas.h"


namespace my {
class NanotechMenuItem : public my::UIItem {
    using super = my::UIItem;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    NanotechMenuItem(const char* name);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
class NanotechMenu : public my::UIPanel, public my::Observer<int> {
    using super = my::UIPanel;
private:
    int _hp;
    //! リソース
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    NanotechMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="hp"></param>
    virtual void OnNotify(int hp) override;
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
#endif // !MY_NANOTECH_MENU_H