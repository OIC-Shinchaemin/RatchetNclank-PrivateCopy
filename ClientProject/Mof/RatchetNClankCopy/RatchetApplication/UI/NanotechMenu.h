#ifndef RATCHET_UI_NANOTECH_MENU_H
#define RATCHET_UI_NANOTECH_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace ratchet::ui {
class NanotechMenuItem : public base::ui::UIItem {
    using super = base::ui::UIItem;
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
class NanotechMenu : public base::ui::UIPanel, 
    public base::core::Observer<int, int> {
    using super = base::ui::UIPanel;
private:
    //! 最大値
    int _hp_max;
    //! Hp
    int _hp;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource_manager;
    //! 拡大率
//<<<<<<< Ex185_BulletActionFix
    float _margin_x;
//=======
    float _scale;
//>>>>>>> MofLib
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
    virtual void OnNotify(int hp, int max) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
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
#endif // !RATCHET_UI_NANOTECH_MENU_H