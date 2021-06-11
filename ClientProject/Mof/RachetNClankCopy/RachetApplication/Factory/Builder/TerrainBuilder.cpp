#include "TerrainBuilder.h"


rachet::TerrainBuilder::TerrainBuilder() :
    super(),
    _resource() {
}

rachet::TerrainBuilder::~TerrainBuilder() {
}

void rachet::TerrainBuilder::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void rachet::TerrainBuilder::Release(void) {
    super::Release();
    _resource.reset();
}

void rachet::TerrainBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto temp = std::any_cast<std::shared_ptr<rachet::Actor>>(shared_this);
    auto ptr = std::dynamic_pointer_cast<rachet::Terrain>(temp);
    ptr->SetResourceManager(_resource);
}