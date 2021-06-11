#ifndef RATCHET_UI_GAME_PAUSE_SYSTEM_MENU_H
#define RATCHET_UI_GAME_PAUSE_SYSTEM_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/GamePauseSystem.h"


namespace ratchet {
namespace ui {
class GamePauseSystemMenuItem : public base::ui::UIItem {
    using super = base::ui::UIItem;
private:
    //! 表示テキスト
    std::string _text;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    GamePauseSystemMenuItem(const char* name);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GamePauseSystemMenuItem();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="text"></param>
    void SetText(const std::string& text);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="tex"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    //bool Initialize(Mof::CVector2 pos, const std::shared_ptr<Mof::CTexture>& tex, const Mof::CVector4& color);
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
class GamePauseSystemMenu : public base::ui::UIPanel,
    public base::core::Observer<const ratchet::game::gamesystem::GamePauseSystem::Info&> {
    using super = base::ui::UIPanel;
    using ElemType = ratchet::ui::GamePauseSystemMenuItem;
private:
    //! 情報
    ratchet::game::gamesystem::GamePauseSystem::Info _infomation;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    GamePauseSystemMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::GamePauseSystem::Info& info) override;
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
    /// 追加
    /// </summary>
    /// <param name="in"></param>
    void AddItem(const ratchet::game::gamesystem::GamePauseSystemItem& in);
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
}
#endif // !RATCHET_UI_GAME_PAUSE_SYSTEM_MENU_H