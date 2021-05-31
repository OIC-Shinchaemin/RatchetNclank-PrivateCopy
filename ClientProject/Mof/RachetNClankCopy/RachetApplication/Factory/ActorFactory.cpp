#include "ActorFactory.h"

#include "../Component/Component.h"
#include "../Actor/Weapon/BombGlove.h"
#include "../Actor/Weapon/Pyrocitor.h"
#include "../Actor/Weapon/Blaster.h"


my::ActorFactory::ActorFactory(my::BuilderFactory* builder_factory) :
    _builder_factory(builder_factory),
    _builders(),
    _mechanical_factory(),
    _game() {
    _mechanical_factory.Register<my::BombGlove>("BombGlove");
    _mechanical_factory.Register<my::Pyrocitor>("Pyrocitor");
    _mechanical_factory.Register<my::Blaster>("Blaster");
}

my::ActorFactory::~ActorFactory() {
    this->Release();
}

void my::ActorFactory::SetGameManager(std::weak_ptr<my::GameManager> ptr) {
    this->_game = ptr;
}

std::shared_ptr<my::IBuilder> my::ActorFactory::GetBuilder(const std::string& key) {
    return this->_builders[key];
}

void my::ActorFactory::AddBuilder(const std::string& key, std::shared_ptr<my::IBuilder> builder) {
    this->_builders[key] = builder;
}

bool my::ActorFactory::Exist(const std::string& type) const {
    auto it = _builders.find(type);
    if (it == _builders.end()) {
        return false;
    } // if
    return true;
}

std::shared_ptr<my::Mechanical> my::ActorFactory::CreateMechanicalWeapon(const char* type, const std::string& builder_key, my::Actor::Param* param) {
    if (!this->Exist(builder_key)) {
        auto builder = _builder_factory->Create(builder_key.c_str());
        this->AddBuilder(builder_key, builder);
    } // if

    auto ptr = _mechanical_factory.Create(type);
    ptr->Construct(_builders.at(builder_key));
    ptr->Initialize(param);
    return ptr;
}

void my::ActorFactory::Release(void) {
    if (!_builders.empty()) {
        _builders.clear();
    } // if
}