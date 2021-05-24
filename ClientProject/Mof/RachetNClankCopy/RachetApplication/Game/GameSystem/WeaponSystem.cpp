#include "WeaponSystem.h"

#include "../../Game/GameManager.h"
#include "../../Factory/FactoryManager.h"
#include "../../UI/EquipmentWeaponMenu.h"


my::WeaponSystem::WeaponSystem() :
    _weapons(),
    _subject(),
    _equipment_subject(),
    _builder_name_map(),
    _save_data(),
    _resource(),
    _ui_canvas() {
    
    _builder_name_map.emplace("BombGlove", "../Resource/builder/bomb_glove.json");
    _builder_name_map.emplace("Pyrocitor", "../Resource/builder/pyrocitor.json");
    _builder_name_map.emplace("Blaster", "../Resource/builder/blaster.json");
}

my::WeaponSystem::~WeaponSystem() {
}

void my::WeaponSystem::OnNotify(const std::string& change) {
    _subject.Notify(this->GetMechanicalWeapon(change));
    auto weapon = this->GetMechanicalWeapon(change);

    int bullet_count = weapon ? weapon->GetBulletCount() : 0;
    
    using namespace std::literals::string_literals;
    std::string_view name = weapon ? weapon->GetName().c_str() : ""s;
    _equipment_subject.Notify(my::Mechanical::Info(bullet_count, name.data()));
}

void my::WeaponSystem::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::WeaponSystem::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

const std::vector<my::WeaponSystem::Pair>& my::WeaponSystem::GetWeaponMap(void) const {
    return this->_weapons;
}

void my::WeaponSystem::AddMechanicalWeaponObserver(const std::shared_ptr<my::Observer<std::shared_ptr<my::Weapon>>>& ptr) {
    _subject.AddObserver(ptr);
}

void my::WeaponSystem::CreateAvailableMechanicalWeaponNames(std::vector<std::string>& out) {
    out.reserve(_weapons.size());
    for (auto& pair : _weapons) {
        out.push_back(pair.first);
    } // for
}

bool my::WeaponSystem::Load(my::SaveData& in) {
    _save_data = in;
    
    auto param = my::Actor::Param();
    for (const auto& key : _save_data.GetAvailableMechanicalWeaponsAddress()) {
        param.name = key;

        auto weapon = my::FactoryManager::Singleton().CreateMechanicalWeapon(
            key.c_str(), _builder_name_map.at(key), &param);
        auto it = std::find_if(_weapons.begin(), _weapons.end(), [key](const my::WeaponSystem::Pair& pair) {
            return pair.first == key;
        });
        if (it == _weapons.end()) {
            _weapons.push_back(std::make_pair(key, weapon));
        } // if
    } // for

    return true;
}

bool my::WeaponSystem::Initialize(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("EquipmentWeaponMenu");
    } // if
    auto menu = std::make_shared< my::EquipmentWeaponMenu>("EquipmentWeaponMenu");
    _equipment_subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if

    // weapon
    auto param = my::Actor::Param();
    for (auto weapon : _weapons) {
        //weapon.second->AddObserver(observer);
        weapon.second->AddMechanicalInfoObserver(menu);
    } // for
    return true;
}

bool my::WeaponSystem::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("EquipmentWeaponMenu");
    } // if
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