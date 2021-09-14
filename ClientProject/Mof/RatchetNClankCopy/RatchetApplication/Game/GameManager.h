#ifndef RATCHET_GAME_GAME_MANAGER_H
#define RATCHET_GAME_GAME_MANAGER_H


#include <memory>

#include "GameSystem/GameSystem.h"
#include "GameSystem/GameMoney.h"
#include "GameSystem/WeaponSystem.h"
#include "GameSystem/QuickChangeSystem.h"
#include "GameSystem/HelpDesk.h"
#include "GameSystem/GameMoney.h"
#include "GameSystem/ShopSystem.h"
#include "GameSystem/OptionSystem.h"
#include "GameSystem/GamePauseSystem.h"


namespace ratchet::game {
class GameManager :
    public std::enable_shared_from_this<ratchet::game::GameManager>,
    public base::core::Observer<const std::shared_ptr<ratchet::game::gamesystem::GameSystem>&> {
private:
    //! 更新用
    std::vector<std::shared_ptr<ratchet::game::gamesystem::GameSystem>> _update_system;
    //! 更新用
    std::vector<std::shared_ptr<ratchet::game::gamesystem::GameSystem>> _disable_systems;
    //! 武器
    std::shared_ptr<ratchet::game::gamesystem::WeaponSystem>  _weapon_system;
    //! クイックチェンジ
    std::shared_ptr<ratchet::game::gamesystem::QuickChangeSystem> _quick_change;
    //! ヘルプデスク
    std::shared_ptr<ratchet::game::gamesystem::HelpDesk>  _help_desk;
    //! お金
    std::shared_ptr<ratchet::game::gamesystem::GameMoney> _game_money;
    //! ショップ
    std::shared_ptr<ratchet::game::gamesystem::ShopSystem> _shop_system;
    //! オプション
    std::shared_ptr<ratchet::game::gamesystem::OptionSystem> _option_system;
    //! ポーズ
    std::shared_ptr<ratchet::game::gamesystem::GamePauseSystem> _pause_system;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;

    template<typename T>
    void SetPtr(T ptr) {
        ptr->SetResourceManager(_resource);
        ptr->SetUICanvas(_ui_canvas);
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameManager();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="ptr"></param>
    virtual void OnNotify(const std::shared_ptr<ratchet::game::gamesystem::GameSystem>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::gamesystem::WeaponSystem> GetWeaponSystem(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::gamesystem::QuickChangeSystem> GetQuickChange(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::gamesystem::HelpDesk> GetHelpDesk(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::gamesystem::GameMoney> GetGameMoney(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::gamesystem::ShopSystem> GetShopSystem(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::gamesystem::OptionSystem> GetOptionSystem(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::gamesystem::GamePauseSystem> GetGamePauseSystem(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    void GameSystemLoad(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    bool Update(float delta_time);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void GameSystemRelease(void);
};
}
#endif // !RATCHET_GAME_GAME_MANAGER_H