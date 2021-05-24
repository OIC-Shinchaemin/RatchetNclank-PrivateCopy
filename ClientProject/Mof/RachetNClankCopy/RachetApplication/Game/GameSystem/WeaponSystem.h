#ifndef MY_WEAPON_SYSTEM_H
#define MY_WEAPON_SYSTEM_H


#include "My/Core/Observer.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "../../Actor/Weapon/Mechanical.h"
#include "../../Factory/Factory.h"


namespace my {
class WeaponSystem : public my::Observer<const std::string&> {
    using Pair = std::pair<std::string, std::shared_ptr<my::Mechanical>>;
private:
    //! 武器
    std::vector<Pair> _weapons;
    //! 通知用
    my::Observable<std::shared_ptr<my::Mechanical>> _subject;
    //! 通知用
    my::Observable<const my::Mechanical::Info&> _equipment_subject;
    //! マップ
    std::unordered_map<std::string, std::string> _builder_name_map;
    //! セーブデータ
    my::SaveData _save_data;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
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
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<my::WeaponSystem::Pair>& GetWeaponMap(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddMechanicalWeaponObserver(const std::shared_ptr<my::Observer<std::shared_ptr<my::Mechanical>>>& ptr);
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
    bool Load(my::SaveData& in);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
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
    std::shared_ptr<my::Mechanical>GetMechanicalWeapon(const std::string& name);
};
}
#endif // !MY_WEAPON_SYSTEM_H