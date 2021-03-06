#include "WeaponSystem.h"

#include "../../Game/GameManager.h"
#include "../../Factory/FactoryManager.h"
#include "../../UI/EquipmentWeaponMenu.h"


ratchet::game::gamesystem::WeaponSystem::WeaponSystem() :
    _weapons(),
    _current_mechanical(),
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

ratchet::game::gamesystem::WeaponSystem::~WeaponSystem() {
}

void ratchet::game::gamesystem::WeaponSystem::OnNotify(const std::string& change) {
    _subject.Notify(this->GetMechanicalWeapon(change));
    auto weapon = this->GetMechanicalWeapon(change);
    if (_current_mechanical) {
        _current_mechanical->SetScale(math::vec3::kZero);
    } // if
    _current_mechanical = weapon;
    int bullet_count = weapon ? weapon->GetBulletCount() : 0;
    int bullet_count_max = weapon ? weapon->GetBulletCountMax() : 0;

    using namespace std::literals::string_literals;
    auto name = weapon ? weapon->GetName().c_str() : ""s;
    _equipment_subject.Notify(ratchet::actor::weapon::Mechanical::Info(bullet_count, bullet_count_max, name.data()));
}

void ratchet::game::gamesystem::WeaponSystem::OnNotify(const ratchet::game::gamesystem::ChargeInfo& info) {
    auto weapon = this->GetMechanicalWeapon(info.type);
    if (info.size) {
        weapon->AddBullet(info.size);
    } // if
    _equipment_subject.Notify(ratchet::actor::weapon::Mechanical::Info(weapon->GetBulletCount(), weapon->GetBulletCountMax(), weapon->GetName().c_str() ));
}

void ratchet::game::gamesystem::WeaponSystem::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::game::gamesystem::WeaponSystem::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

std::shared_ptr<ratchet::actor::weapon::Mechanical> ratchet::game::gamesystem::WeaponSystem::GetCurrentMechanicalWeapon(void) const {
    return this->_current_mechanical;
}

const std::vector<ratchet::game::gamesystem::WeaponSystem::Pair>& ratchet::game::gamesystem::WeaponSystem::GetWeaponMap(void) const {
    return this->_weapons;
}

void ratchet::game::gamesystem::WeaponSystem::AddMechanicalWeaponObserver(const std::shared_ptr<base::core::Observer<std::shared_ptr<ratchet::actor::weapon::Weapon>>>& ptr) {
    _subject.AddObserver(ptr);
}

void ratchet::game::gamesystem::WeaponSystem::CreateAvailableMechanicalWeaponNames(std::vector<std::string>& out) {
    out.reserve(_weapons.size());
    for (auto& pair : _weapons) {
        out.push_back(pair.first);
    } // for
}

bool ratchet::game::gamesystem::WeaponSystem::Load(ratchet::game::gamesystem::save::SaveData& in) {
    _save_data = in;

    auto param = ratchet::actor::Actor::Param();
    for (const auto& key : _save_data.GetAvailableMechanicalWeaponsAddress()) {
        param.name = key;

        auto weapon = ratchet::factory::FactoryManager::Singleton().CreateMechanicalWeapon(
            key.c_str(), _builder_name_map.at(key), &param);
        auto it = std::find_if(_weapons.begin(), _weapons.end(), [key](const ratchet::game::gamesystem::WeaponSystem::Pair& pair) {
            return pair.first == key;
        });
        if (it == _weapons.end()) {
            _weapons.push_back(std::make_pair(key, weapon));
        } // if
    } // for

    return true;
}

bool ratchet::game::gamesystem::WeaponSystem::Initialize(const std::shared_ptr<base::core::Observer<const char*, const std::shared_ptr<ratchet::actor::Actor>&>>& observer) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("EquipmentWeaponMenu");
    } // if
    auto menu = std::make_shared< ratchet::ui::EquipmentWeaponMenu>("EquipmentWeaponMenu");
    _equipment_subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if

    // weapon
    auto param = ratchet::actor::Actor::Param();
    for (auto weapon : _weapons) {
        weapon.second->AddObserver(observer);
        weapon.second->AddMechanicalInfoObserver(menu);
    } // for
    return true;
}

bool ratchet::game::gamesystem::WeaponSystem::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("EquipmentWeaponMenu");
    } // if
    return true;
}

std::shared_ptr<ratchet::actor::weapon::Mechanical> ratchet::game::gamesystem::WeaponSystem::GetMechanicalWeapon(const std::string& name) {
    _current_mechanical.reset();
    auto it = std::find_if(_weapons.begin(), _weapons.end(), [&](Pair& pair) {
        return pair.first == name;
    });
    if (it != _weapons.end()) {
        return it->second;
    } // if
    return nullptr;
}