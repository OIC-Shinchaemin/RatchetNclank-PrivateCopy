#ifndef RATCHET_UI_GAME_MONEY_MENU_H
#define RATCHET_UI_GAME_MONEY_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/GameMoney.h"
#include "Base/Core/Timer.h"


namespace ratchet ::ui {
class GameMoneyMenu : public base::ui::UIPanel,
    public ratchet::game::gamesystem::GameMoneyMessageListener {
    using super = base::ui::UIPanel;
private:
    //! お金
    int _money;
    //! お金
    int _money_max;
    //! 表示
    bool _show;
    //! 時間
    float _time_max;
    //! 非表示タイマー
    base::core::Timer _hide_timer;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    GameMoneyMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="money"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::GameMoneyMessage& message) override;
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
#endif // !RATCHET_UI_GAME_MONEY_MENU_H