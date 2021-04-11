#include "WeaponSystem.h"

#include "../Game/GameManager.h"
#include "../Factory/FactoryManager.h"


my::WeaponSystem::WeaponSystem() :
    _weapons(),
    _subject(),
    _builder_name_map() {

    _builder_name_map.emplace("BombGlove", "../Resource/builder/bomb_glove.json");
    _builder_name_map.emplace("Pyrocitor", "../Resource/builder/pyrocitor.json");
    _builder_name_map.emplace("Blaster", "../Resource/builder/blaster.json");
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

    auto param = my::Actor::Param();
    for (const auto& key : in.GetAvailableMechanicalWeaponsAddress()) {
        param.name = key;

        auto add = my::FactoryManager::Singleton().CreateMechanicalWeapon(
            key.c_str(), _builder_name_map.at(key), &param
        );
        add->AddObserver(observer);
        _weapons.push_back(std::make_pair(key, add));
    } // for
    return true;
}

std::shared_ptr<my::Mechanical> my::WeaponSystem::GetMechanicalWeapon(const std::string& name) {
    auto it = std::find_if(_weapons.begin(), _weapons.end(), [&](Pair& pair) {
        return pair.first == name;
    });
    if (it != _weapons.end()) {
        return it->second;
    } // if
    return nullptr;
}