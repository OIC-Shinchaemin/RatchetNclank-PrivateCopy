#ifndef MY_WEAPON_SYSTEM_H
#define MY_WEAPON_SYSTEM_H


#include "My/Core/Observer.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "My/Core/Observable.h"
#include "Save/SaveData.h"
#include "../Weapon/Weapon.h"
#include "../Factory/Factory.h"


namespace my {
class WeaponSystem : public my::Observer<const std::string&> {
private:
    //! 武器
    std::unordered_map<std::string, std::shared_ptr<my::Weapon>> _weapons;
    //! 通知用
    my::Observable<std::shared_ptr<my::Weapon>> _current;
    //! ファクトリー
    my::Factory<my::Weapon> _factory;
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
    void AddWeaponObserver(const std::shared_ptr<my::Observer<std::shared_ptr<my::Weapon>>> &ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="out"></param>
    void CreateAvailableWeaponNames(std::vector<std::string>& out);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Initialize(my::SaveData& in);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<my::Weapon>GetWeapon(const std::string& name);
};
}
#endif // !MY_WEAPON_SYSTEM_H