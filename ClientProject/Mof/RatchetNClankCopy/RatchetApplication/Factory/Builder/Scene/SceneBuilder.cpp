#include "SceneBuilder.h"


ratchet::factory::builder::scene::SceneBuilder::SceneBuilder() :
    super(),
    _resource(),
    _ui_canvas() {
}

ratchet::factory::builder::scene::SceneBuilder::~SceneBuilder() {
}

void ratchet::factory::builder::scene::SceneBuilder::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::factory::builder::scene::SceneBuilder::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas= ptr;
}

void ratchet::factory::builder::scene::SceneBuilder::Release(void) {
    _resource.reset();
    _ui_canvas.reset();
}

void ratchet::factory::builder::scene::SceneBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<ratchet::scene::Scene>>(shared_this);
    ptr->SetResourceManager(_resource);
    ptr->SetUICanvas(_ui_canvas);
}