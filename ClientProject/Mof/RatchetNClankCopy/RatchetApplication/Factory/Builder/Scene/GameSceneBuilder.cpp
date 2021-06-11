#include "GameSceneBuilder.h"


builder::GameSceneBuilder::GameSceneBuilder() :
    super(),
    _game(),
    _event() {
}

builder::GameSceneBuilder::~GameSceneBuilder() {
}

void builder::GameSceneBuilder::SetGameManager(std::weak_ptr<ratchet::GameManager> ptr) {
    this->_game = ptr;
}

void builder::GameSceneBuilder::SetEventManager(std::weak_ptr<ratchet::EventManager> ptr) {
    this->_event = ptr;
}

void builder::GameSceneBuilder::Release(void) {
    super::Release();
    _game.reset();
    _event.reset();
}

void builder::GameSceneBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto ptr = std::dynamic_pointer_cast<ratchet::GameScene>(std::any_cast<std::shared_ptr<ratchet::Scene>>(shared_this));
    ptr->SetGameManager(_game);
    ptr->SetEventManager(_event);
}