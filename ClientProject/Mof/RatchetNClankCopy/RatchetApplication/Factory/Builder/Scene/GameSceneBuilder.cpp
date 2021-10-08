#include "GameSceneBuilder.h"


ratchet::factory::builder::scene::GameSceneBuilder::GameSceneBuilder() :
    super(),
    _game(),
    _event(),
    _light() {
}

ratchet::factory::builder::scene::GameSceneBuilder::~GameSceneBuilder() {
}

void ratchet::factory::builder::scene::GameSceneBuilder::SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr) {
    this->_game = ptr;
}

void ratchet::factory::builder::scene::GameSceneBuilder::SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr) {
    this->_event = ptr;
}

void ratchet::factory::builder::scene::GameSceneBuilder::SetLightManager(std::weak_ptr<ratchet::light::LightManager> ptr) {
    this->_light = ptr;
}

void ratchet::factory::builder::scene::GameSceneBuilder::Release(void) {
    super::Release();
    _game.reset();
    _event.reset();
    _light.reset();
}

void ratchet::factory::builder::scene::GameSceneBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto ptr = std::dynamic_pointer_cast<ratchet::scene::GameScene>(std::any_cast<std::shared_ptr<ratchet::scene::Scene>>(shared_this));
    ptr->SetGameManager(_game);
    ptr->SetEventManager(_event);
    ptr->SetLightManager(_light);
}