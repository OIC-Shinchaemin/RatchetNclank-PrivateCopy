#include "TerrainBuilder.h"


my::TerrainBuilder::TerrainBuilder() :
    super(),
    _resource() {
}

my::TerrainBuilder::~TerrainBuilder() {
}

void my::TerrainBuilder::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::TerrainBuilder::Release(void) {
    super::Release();
    _resource.reset();
}

void my::TerrainBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto temp = std::any_cast<std::shared_ptr<my::Actor>>(shared_this);
    auto ptr = std::dynamic_pointer_cast<my::Terrain>(temp);
    ptr->SetResourceManager(_resource);
}