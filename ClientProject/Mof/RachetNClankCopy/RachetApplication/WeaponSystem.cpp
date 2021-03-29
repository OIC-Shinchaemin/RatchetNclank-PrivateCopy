#include "WeaponSystem.h"

#include "Weapon/OmniWrench.h"
#include "Weapon/BombGlove.h"
#include "Weapon/Pyrocitor.h"


my::WeaponSystem::WeaponSystem() :
    _weapons(),
    _factory(){

    _factory.Register<my::OmniWrench>("OmniWrench");
    _factory.Register<my::BombGlove>("BombGlove");
    _factory.Register<my::Pyrocitor>("Pyrocitor");
}

my::WeaponSystem::~WeaponSystem() {
}

void my::WeaponSystem::CreateAvailableWeaponNames(std::vector<std::string>& out) {
    out.reserve(_weapons.size());
    for (auto& pair : _weapons) {
        out.push_back(pair.first);
    } // for
}

bool my::WeaponSystem::Initialize(my::SaveData& in) {
    for (const auto& key : in.GetAvailableWeaponsAddress()) {
        _weapons.emplace(key, _factory.Create(key));
    } // for
    return true;
}

std::shared_ptr<my::Weapon> my::WeaponSystem::GetWeapon(const std::string& name) {
    auto it = _weapons.find(name);
    if (it != _weapons.end()) {
        return it->second;
    } // if
    return nullptr;
}