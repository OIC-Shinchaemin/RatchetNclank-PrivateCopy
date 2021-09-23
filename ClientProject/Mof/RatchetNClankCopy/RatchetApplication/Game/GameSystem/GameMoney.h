#ifndef RATCHET_GAME_GAME_SYSTEM_GAME_MONEY_H
#define RATCHET_GAME_GAME_SYSTEM_GAME_MONEY_H


#include <memory>
#include <string>

#include <Mof.h>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "Save/SaveData.h"


namespace ratchet::game::gamesystem {
struct GameMoneyMessage {
    int money;
    int money_max;
};
using GameMoneyMessageSubject = base::core::Observable<const GameMoneyMessage&>;
using GameMoneyMessageListener = base::core::Observer<const GameMoneyMessage&>;

class GameMoney :
    public std::enable_shared_from_this<ratchet::game::gamesystem::GameMoney>,
    public base::core::Observer<int> {
private:
    //! お金
    std::uint32_t _value;
    //! お金
    std::uint32_t _value_max;
    //! 通知用
    //base::core::Observable<int> _subject;
    GameMoneyMessageSubject _subject;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameMoney();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameMoney();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(int add_money) override;
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::uint32_t GetValue(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Load(ratchet::game::gamesystem::save::SaveData& in);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_GAME_MONEY_H