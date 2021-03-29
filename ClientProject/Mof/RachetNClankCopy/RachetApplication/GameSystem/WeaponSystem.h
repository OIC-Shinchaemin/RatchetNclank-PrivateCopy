#ifndef MY_WEAPON_SYSTEM_H
#define MY_WEAPON_SYSTEM_H


#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "Save/SaveData.h"
#include "../Weapon/Weapon.h"
#include "../Factory/Factory.h"


namespace my {
class WeaponSystem {
private:
    //! 武器
    std::unordered_map<std::string, std::shared_ptr<my::Weapon>> _weapons;
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
    std::shared_ptr<my::Weapon> GetWeapon(const std::string& name);
};
}
#endif // !MY_WEAPON_SYSTEM_H