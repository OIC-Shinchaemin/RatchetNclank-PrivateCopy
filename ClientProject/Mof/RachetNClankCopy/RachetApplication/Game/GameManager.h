#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H


#include <memory>

#include "GameSystem/GameMoney.h"
#include "GameSystem/WeaponSystem.h"
#include "GameSystem/QuickChangeSystem.h"


namespace my {
class GameManager : public std::enable_shared_from_this<my::GameManager> {
private:
    //! 武器
    std::shared_ptr<my::WeaponSystem>  _weapon_system;
    //! クイックチェンジ
    std::shared_ptr<my::QuickChangeSystem>  _quick_change;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
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
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::WeaponSystem> GetWeaponSystem(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::QuickChangeSystem> GetQuickChange(void) const;
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
    /// <returns></returns>
    bool Update(void);
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
#endif // !MY_GAME_MANAGER_H