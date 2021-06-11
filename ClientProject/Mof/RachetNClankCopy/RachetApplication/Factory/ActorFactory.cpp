#include "ActorFactory.h"

#include "../Component/Component.h"
#include "../Actor/Weapon/BombGlove.h"
#include "../Actor/Weapon/Pyrocitor.h"
#include "../Actor/Weapon/Blaster.h"


rachet::ActorFactory::ActorFactory(rachet::BuilderFactory* builder_factory) :
    _builder_factory(builder_factory),
    _builders(),
    _mechanical_factory(),
    _game() {
    _mechanical_factory.Register<rachet::BombGlove>("BombGlove");
    _mechanical_factory.Register<rachet::Pyrocitor>("Pyrocitor");
    _mechanical_factory.Register<rachet::Blaster>("Blaster");
}

rachet::ActorFactory::~ActorFactory() {
    this->Release();
}

void rachet::ActorFactory::SetGameManager(std::weak_ptr<rachet::GameManager> ptr) {
    this->_game = ptr;
}

std::shared_ptr<rachet::IBuilder> rachet::ActorFactory::GetBuilder(const std::string& key) {
    return this->_builders[key];
}

void rachet::ActorFactory::AddBuilder(const std::string& key, std::shared_ptr<rachet::IBuilder> builder) {
    this->_builders[key] = builder;
}

bool rachet::ActorFactory::Exist(const std::string& type) const {
    auto it = _builders.find(type);
    if (it == _builders.end()) {
        return false;
    } // if
    return true;
}

std::shared_ptr<rachet::Mechanical> rachet::ActorFactory::CreateMechanicalWeapon(const char* type, const std::string& builder_key, rachet::Actor::Param* param) {
    if (!this->Exist(builder_key)) {
        auto builder = _builder_factory->Create(builder_key.c_str());
        this->AddBuilder(builder_key, builder);
    } // if

    auto ptr = _mechanical_factory.Create(type);
    ptr->Construct(_builders.at(builder_key));
    ptr->Initialize(param);
    return ptr;
}

void rachet::ActorFactory::Release(void) {
    if (!_builders.empty()) {
        _builders.clear();
    } // if
}