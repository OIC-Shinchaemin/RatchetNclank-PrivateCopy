#ifndef MY_NANOTECH_MENU_H
#define MY_NANOTECH_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


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
    //! 最大値
    int _hp_max;
    //! Hp
    int _hp;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource_manager;
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
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_NANOTECH_MENU_H