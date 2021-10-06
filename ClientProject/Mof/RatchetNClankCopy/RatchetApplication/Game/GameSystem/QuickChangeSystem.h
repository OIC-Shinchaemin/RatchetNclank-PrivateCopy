#ifndef RATCHET_GAME_GAME_SYSTEM_QUICK_CHANGE_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_QUICK_CHANGE_SYSTEM_H


#include "GameSystem.h"
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


namespace ratchet::game::gamesystem {
class QuickChangeItem {
private:
    //! 所有
    std::string _weapon;
public:
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="name"></param>
    void SetWeapon(const char* name);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetWeapon(void) const;
};

class QuickChangeSystem :
    public ratchet::game::gamesystem::GameSystem {
    using super = ratchet::game::gamesystem::GameSystem;
    using This = ratchet::game::gamesystem::QuickChangeSystem;
    using Observable = base::core::Observable<Mof::CVector4>;
    enum class State {
        Enter,
        Exit
    };
public:
    struct Info {
        //! 表示色
        Mof::CVector4 color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.0f);
        //! 現在
        std::optional<int> current_index;
    };
private:
    //! 色
    This::Info _infomation;
    //! 状態
    State _state;
    //! アルファ
    float _alpha;
    //! 半径
    float _distance;
    //! 武器
    std::vector<int> _angles;
    //! アイテム
    std::unordered_map<int, ratchet::game::gamesystem::QuickChangeItem> _items;
    //! 通知用
    base::core::Observable<const std::string&> _current;
    //! 監視対象
    base::core::Observable<const This::Info&> _info_subject;
    //! 指定の武器のインデックス
    int _blaster_index;
    //! 指定の武器のインデックス
    int _empty_index;
    //! 切り替えのワーク変数
    int _work_index;
    /// <summary>
    /// 開く
    /// </summary>
    /// <param name=""></param>
    void Open(void);
    /// <summary>
    /// 閉じる
    /// </summary>
    /// <param name=""></param>
    void Close(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    QuickChangeSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~QuickChangeSystem();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector4 GetColor(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddWeaponObserver(const std::shared_ptr<base::core::Observer<const std::string&>>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddInfoObserver(const std::shared_ptr<base::core::Observer<const ratchet::game::gamesystem::QuickChangeSystem::Info&>>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="weapon_system"></param>
    /// <returns></returns>
    bool Initialize(const std::shared_ptr<ratchet::game::gamesystem::WeaponSystem>& weapon_system);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_QUICK_CHANGE_SYSTEM_H