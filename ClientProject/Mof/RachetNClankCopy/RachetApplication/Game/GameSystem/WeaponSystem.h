#ifndef RACHET_WEAPON_SYSTEM_H
#define RACHET_WEAPON_SYSTEM_H


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


namespace rachet {
struct ChargeInfo {
    //! 武器
    std::string type;
    //! 装填数
    std::uint32_t size;
};
class WeaponSystem : 
    public base::core::Observer<const std::string&>,
    public base::core::Observer<const rachet::ChargeInfo&>
{
    using Pair = std::pair<std::string, std::shared_ptr<rachet::Mechanical>>;
private:
    //! 武器
    std::vector<Pair> _weapons;
    //! 武器
    std::shared_ptr<rachet::Mechanical> _current_mechanical;
    //! 通知用
    base::core::Observable<std::shared_ptr<rachet::Weapon>> _subject;
    //! 通知用
    base::core::Observable<const rachet::Mechanical::Info&> _equipment_subject;
    //! マップ
    std::unordered_map<std::string, std::string> _builder_name_map;
    //! セーブデータ
    rachet::SaveData _save_data;
    //! リソース
    std::weak_ptr<rachet::ResourceMgr> _resource;
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
    virtual void OnNotify(const rachet::ChargeInfo& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
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
    std::shared_ptr<rachet::Mechanical> GetCurrentMechanicalWeapon(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<rachet::WeaponSystem::Pair>& GetWeaponMap(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddMechanicalWeaponObserver(const std::shared_ptr<base::core::Observer<std::shared_ptr<rachet::Weapon>>>& ptr);
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
    bool Load(rachet::SaveData& in);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="observer"></param>
    /// <returns></returns>
    bool Initialize(const std::shared_ptr<base::core::Observer<const char*, const std::shared_ptr<rachet::Actor>&>>& observer);
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
    std::shared_ptr<rachet::Mechanical>GetMechanicalWeapon(const std::string& name);
};
}
#endif // !RACHET_WEAPON_SYSTEM_H