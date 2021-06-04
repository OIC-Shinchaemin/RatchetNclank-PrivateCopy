#include "SceneBuilder.h"


builder::SceneBuilder::SceneBuilder() :
    super(),
    _resource() {
}

builder::SceneBuilder::~SceneBuilder() {
}

void builder::SceneBuilder::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void builder::SceneBuilder::Release(void) {
    _resource.reset();
}

void builder::SceneBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<my::Scene>>(shared_this);
    ptr->SetResourceManager(_resource);
}