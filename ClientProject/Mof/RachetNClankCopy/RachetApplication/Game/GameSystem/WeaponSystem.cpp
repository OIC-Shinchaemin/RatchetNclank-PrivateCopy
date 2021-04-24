#include "WeaponSystem.h"

#include "../../Game/GameManager.h"
#include "../../Factory/FactoryManager.h"
#include "../../UI/EquipmentWeaponMenu.h"


my::WeaponSystem::WeaponSystem() :
    _weapons(),
    _subject(),
    _equipment_subject(),
    _builder_name_map(),
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
    std::string name = weapon ? weapon->GetName().c_str() : "";
    _equipment_subject.Notify(my::Mechanical::Info(bullet_count, name.c_str()));
}

void my::WeaponSystem::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::WeaponSystem::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
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

bool my::WeaponSystem::Initialize(my::SaveData& in, const std::shared_ptr<my::Observer<const char*, const std::shared_ptr<my::Actor>&>>&  observer) {
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

    auto param = my::Actor::Param();
    for (const auto& key : in.GetAvailableMechanicalWeaponsAddress()) {
        param.name = key;

        auto weapon = my::FactoryManager::Singleton().CreateMechanicalWeapon(
            key.c_str(), _builder_name_map.at(key), &param);
        weapon->AddObserver(observer);
        weapon->AddMechanicalInfoObserver(menu);
        auto it = std::find_if(_weapons.begin(), _weapons.end(), [key](const my::WeaponSystem::Pair& pair) {
            return pair.first == key;
        });
        if (it == _weapons.end()) {
            _weapons.push_back(std::make_pair(key, weapon));
        } // if
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