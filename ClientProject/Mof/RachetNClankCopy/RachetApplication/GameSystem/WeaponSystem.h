#ifndef MY_WEAPON_SYSTEM_H
#define MY_WEAPON_SYSTEM_H


#include "My/Core/Observer.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "My/Core/Observable.h"
#include "Save/SaveData.h"
#include "../Actor/Weapon/Mechanical.h"
#include "../Factory/Factory.h"


namespace my {
class WeaponSystem : public my::Observer<const std::string&> {
    using Pair = std::pair<std::string, std::shared_ptr<my::Mechanical>>;
private:
    //! 武器
    std::vector<Pair> _weapons;
    //! 通知用
    my::Observable<std::shared_ptr<my::Mechanical>> _subject;
    //! マップ
    std::unordered_map<std::string, std::string> _builder_name_map;
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
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddMechanicalWeaponObserver(const std::shared_ptr<my::Observer<std::shared_ptr<my::Mechanical>>> &ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="out"></param>
    void CreateAvailableMechanicalWeaponNames(std::vector<std::string>& out);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="in"></param>
    /// <param name="observer"></param>
    /// <returns></returns>
    bool Initialize(my::SaveData& in, const std::shared_ptr<class GameManager>& observer);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<my::Mechanical>GetMechanicalWeapon(const std::string& name);
};
}
#endif // !MY_WEAPON_SYSTEM_H