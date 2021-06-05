#include "TitleSceneBuilder.h"


builder::TitleSceneBuilder::TitleSceneBuilder() :
    super(),
    _game() {
}

builder::TitleSceneBuilder::~TitleSceneBuilder() {
}
/*
void builder::TitleSceneBuilder::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}
*/
void builder::TitleSceneBuilder::SetGameManager(std::weak_ptr<my::GameManager> ptr) {
    this->_game = ptr;
}

void builder::TitleSceneBuilder::Release(void) {
    super::Release();
    _game.reset();
}

void builder::TitleSceneBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    //auto ptr = std::any_cast<std::shared_ptr<my::GameScene>>(shared_this);
    auto ptr = std::dynamic_pointer_cast<my::TitleScene>(std::any_cast<std::shared_ptr<my::Scene>>(shared_this));
    ptr->SetGameManager(_game);
}