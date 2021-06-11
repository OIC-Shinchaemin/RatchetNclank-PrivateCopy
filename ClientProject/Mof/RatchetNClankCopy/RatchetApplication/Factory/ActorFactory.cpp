#include "ActorFactory.h"

#include "../Component/Component.h"
#include "../Actor/Weapon/BombGlove.h"
#include "../Actor/Weapon/Pyrocitor.h"
#include "../Actor/Weapon/Blaster.h"


ratchet::factory::ActorFactory::ActorFactory(ratchet::factory::BuilderFactory* builder_factory) :
    _builder_factory(builder_factory),
    _builders(),
    _mechanical_factory(),
    _game() {
    _mechanical_factory.Register<ratchet::actor::weapon::BombGlove>("BombGlove");
    _mechanical_factory.Register<ratchet::actor::weapon::Pyrocitor>("Pyrocitor");
    _mechanical_factory.Register<ratchet::actor::weapon::Blaster>("Blaster");
}

ratchet::factory::ActorFactory::~ActorFactory() {
    this->Release();
}

void ratchet::factory::ActorFactory::SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr) {
    this->_game = ptr;
}

std::shared_ptr<ratchet::factory::builder::IBuilder> ratchet::factory::ActorFactory::GetBuilder(const std::string& key) {
    return this->_builders[key];
}

void ratchet::factory::ActorFactory::AddBuilder(const std::string& key, std::shared_ptr<ratchet::factory::builder::IBuilder> builder) {
    this->_builders[key] = builder;
}

bool ratchet::factory::ActorFactory::Exist(const std::string& type) const {
    auto it = _builders.find(type);
    if (it == _builders.end()) {
        return false;
    } // if
    return true;
}

std::shared_ptr<ratchet::actor::weapon::Mechanical> ratchet::factory::ActorFactory::CreateMechanicalWeapon(const char* type, const std::string& builder_key, ratchet::actor::Actor::Param* param) {
    if (!this->Exist(builder_key)) {
        auto builder = _builder_factory->Create(builder_key.c_str());
        this->AddBuilder(builder_key, builder);
    } // if

    auto ptr = _mechanical_factory.Create(type);
    ptr->Construct(_builders.at(builder_key));
    ptr->Initialize(param);
    return ptr;
}

void ratchet::factory::ActorFactory::Release(void) {
    if (!_builders.empty()) {
        _builders.clear();
    } // if
}