#include "TitleSceneBuilder.h"


builder::TitleSceneBuilder::TitleSceneBuilder() :
    super(),
    _game() {
}

builder::TitleSceneBuilder::~TitleSceneBuilder() {
}
/*
void builder::TitleSceneBuilder::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}
*/
void builder::TitleSceneBuilder::SetGameManager(std::weak_ptr<rachet::GameManager> ptr) {
    this->_game = ptr;
}

void builder::TitleSceneBuilder::Release(void) {
    super::Release();
    _game.reset();
}

void builder::TitleSceneBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    //auto ptr = std::any_cast<std::shared_ptr<rachet::GameScene>>(shared_this);
    auto ptr = std::dynamic_pointer_cast<rachet::TitleScene>(std::any_cast<std::shared_ptr<rachet::Scene>>(shared_this));
    ptr->SetGameManager(_game);
}