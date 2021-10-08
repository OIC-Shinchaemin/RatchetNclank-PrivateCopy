#ifndef RATCHET_GAME_GAME_SYSTEM_GAME_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_GAME_SYSTEM_H


#include "Base/Core/Observable.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "WeaponSystem.h"
#include "Base/UI/UICanvas.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "../Audio/SoundPlayer.h"


namespace ratchet::game::gamesystem {
class GameSystem : 
    public std::enable_shared_from_this<ratchet::game::gamesystem::GameSystem>,
    public base::core::Observer<bool> {
private:
    //! 通知用
    base::core::Observable<const std::shared_ptr<GameSystem>&> _subject;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! SE
    std::weak_ptr<ratchet::game::audio::SEPlayer> _se_player;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::ResourceMgr> GetResource(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<base::ui::UICanvas> GetUICanvas(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::game::audio::SEPlayer> GetSEPlayer(void) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameSystem();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
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
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetSEPlayer(std::weak_ptr<ratchet::game::audio::SEPlayer> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const std::shared_ptr<GameSystem>&>* GetSubject(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Update(float delta_time);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_GAME_SYSTEM_H