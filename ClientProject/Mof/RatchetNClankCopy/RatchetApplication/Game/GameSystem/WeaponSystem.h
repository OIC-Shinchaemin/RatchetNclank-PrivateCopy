#ifndef RATCHET_GAME_GAME_SYSTEM_WEAPON_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_WEAPON_SYSTEM_H


#include "Base/Core/Observer.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "../../Actor/Weapon/Mechanical.h"
#include "../../Factory/Factory.h"


namespace ratchet::game::gamesystem {
struct ChargeInfo {
    //! 武器
    std::string type;
    //! 装填数
    std::uint32_t size;
};
class WeaponSystem :
    public base::core::Observer<const std::string&>,
    public base::core::Observer<const ratchet::game::gamesystem::ChargeInfo&> {
    using Pair = std::pair<std::string, std::shared_ptr<ratchet::actor::weapon::Mechanical>>;
private:
    //! 武器
    std::vector<Pair> _weapons;
    //! 武器
    std::shared_ptr<ratchet::actor::weapon::Mechanical> _current_mechanical;
    //! 通知用
    base::core::Observable<std::shared_ptr<ratchet::actor::weapon::Weapon>> _subject;
    //! 通知用
    base::core::Observable<const ratchet::actor::weapon::Mechanical::Info&> _equipment_subject;
    //! マップ
    std::unordered_map<std::string, std::string> _builder_name_map;
    //! セーブデータ
    ratchet::game::gamesystem::save::SaveData _save_data;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    WeaponSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~WeaponSystem();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const std::string& change) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::ChargeInfo& info) override;
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
    std::shared_ptr<ratchet::actor::weapon::Mechanical> GetCurrentMechanicalWeapon(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<ratchet::game::gamesystem::WeaponSystem::Pair>& GetWeaponMap(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddMechanicalWeaponObserver(const std::shared_ptr<base::core::Observer<std::shared_ptr<ratchet::actor::weapon::Weapon>>>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="out"></param>
    void CreateAvailableMechanicalWeaponNames(std::vector<std::string>& out);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Load(ratchet::game::gamesystem::save::SaveData& in);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="observer"></param>
    /// <returns></returns>
    bool Initialize(const std::shared_ptr<base::core::Observer<const char*, const std::shared_ptr<ratchet::actor::Actor>&>>& observer);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::weapon::Mechanical>GetMechanicalWeapon(const std::string& name);
    /// <summary>
    /// 弾薬満タン
    /// </summary>
    /// <param name=""></param>
    void FullCharge(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_WEAPON_SYSTEM_H