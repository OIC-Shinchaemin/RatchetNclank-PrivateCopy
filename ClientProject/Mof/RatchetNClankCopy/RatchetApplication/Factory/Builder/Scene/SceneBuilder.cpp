#include "SceneBuilder.h"


builder::SceneBuilder::SceneBuilder() :
    super(),
    _resource(),
    _ui_canvas() {
}

builder::SceneBuilder::~SceneBuilder() {
}

void builder::SceneBuilder::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void builder::SceneBuilder::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas= ptr;
}

void builder::SceneBuilder::Release(void) {
    _resource.reset();
    _ui_canvas.reset();
}

void builder::SceneBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<ratchet::Scene>>(shared_this);
    ptr->SetResourceManager(_resource);
    ptr->SetUICanvas(_ui_canvas);
}