#ifndef MY_SHOP_SYSTEM_MENU_H
#define MY_SHOP_SYSTEM_MENU_H


#include "My/UI/UIItem.h"
#include "My/UI/UIPanel.h"

#include <memory>

#include "My/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/ShopSystem.h"


namespace my {
class ShopSystemMenuItem : public my::UIItem {
    using super = my::UIItem;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    ShopSystemMenuItem(const char* name);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
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
class ShopSystemMenu : public my::UIPanel, public my::Observer<const my::ShopSystem::Info&> {
    using super = my::UIPanel;
private:
    //! 表示
    bool _show;
    //! 情報
    my::ShopSystem::Info _infomation;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    ShopSystemMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="money"></param>
    virtual void OnNotify(const my::ShopSystem::Info& info) override;
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
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_SHOP_SYSTEM_MENU_H