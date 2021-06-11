#include "TitleSceneBuilder.h"


ratchet::factory::builder::scene::TitleSceneBuilder::TitleSceneBuilder() :
    super(),
    _game() {
}

ratchet::factory::builder::scene::TitleSceneBuilder::~TitleSceneBuilder() {
}

void ratchet::factory::builder::scene::TitleSceneBuilder::SetGameManager(std::weak_ptr<ratchet::GameManager> ptr) {
    this->_game = ptr;
}

void ratchet::factory::builder::scene::TitleSceneBuilder::Release(void) {
    super::Release();
    _game.reset();
}

void ratchet::factory::builder::scene::TitleSceneBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto ptr = std::dynamic_pointer_cast<ratchet::scene::TitleScene>(std::any_cast<std::shared_ptr<ratchet::scene::Scene>>(shared_this));
    ptr->SetGameManager(_game);
}