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
    //! ����
    std::unordered_map<std::string, std::shared_ptr<my::Weapon>> _weapons;
    //! �t�@�N�g���[
    my::Factory<my::Weapon> _factory;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    WeaponSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~WeaponSystem();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="out"></param>
    void CreateAvailableWeaponNames(std::vector<std::string>& out);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Initialize(my::SaveData& in);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<my::Weapon> GetWeapon(const std::string& name);
};
}
#endif // !MY_WEAPON_SYSTEM_H