#include "SceneBuilder.h"


my::SceneBuilder::SceneBuilder() :
    super(),
    _resource() {
}

my::SceneBuilder::~SceneBuilder() {
}
void my::SceneBuilder::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::SceneBuilder::Release(void) {
    _resource.reset();
}

void my::SceneBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<my::Scene>>(shared_this);
    ptr->SetResourceManager(_resource);
}