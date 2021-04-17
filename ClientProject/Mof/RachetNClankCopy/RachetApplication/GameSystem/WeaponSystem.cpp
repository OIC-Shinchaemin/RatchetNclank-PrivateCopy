#include "WeaponSystem.h"

#include "../Game/GameManager.h"
#include "../Weapon/OmniWrench.h"
#include "../Weapon/BombGlove.h"
#include "../Weapon/Pyrocitor.h"
#include "../Weapon/Blaster.h"


my::WeaponSystem::WeaponSystem() :
    _weapons(),
    _factory() ,
    _subject(){

    //_factory.Register<my::OmniWrench>("OmniWrench");
    _factory.Register<my::BombGlove>("BombGlove");
    _factory.Register<my::Pyrocitor>("Pyrocitor");
    _factory.Register<my::Blaster>("Blaster");
}

my::WeaponSystem::~WeaponSystem() {
}

void my::WeaponSystem::OnNotify(const std::string& change) {
    _subject.Notify(this->GetMechanicalWeapon(change));
}

void my::WeaponSystem::AddMechanicalWeaponObserver(const std::shared_ptr<my::Observer<std::shared_ptr<my::Mechanical>>>& ptr) {
    _subject.AddObserver(ptr);
}

void my::WeaponSystem::CreateAvailableMechanicalWeaponNames(std::vector<std::string>& out) {
    out.reserve(_weapons.size());
    for (auto& pair : _weapons) {
        out.push_back(pair.first);
    } // for
}

bool my::WeaponSystem::Initialize(my::SaveData& in, const std::shared_ptr<my::GameManager>& observer) {
    for (const auto& key : in.GetAvailableMechanicalWeaponsAddress()) {
        auto add = _factory.Create(key);
        add->AddObserver(observer);
        _weapons.push_back(std::make_pair(key, add));
    } // for
    return true;
}

std::shared_ptr<my::Mechanical> my::WeaponSystem::GetMechanicalWeapon(const std::string& name) {
    auto it =  std::find_if(_weapons.begin(), _weapons.end(), [&](Pair& pair) {
        return pair.first == name;
    });
    if (it != _weapons.end()) {
        return it->second;
    } // if
    return nullptr;
}