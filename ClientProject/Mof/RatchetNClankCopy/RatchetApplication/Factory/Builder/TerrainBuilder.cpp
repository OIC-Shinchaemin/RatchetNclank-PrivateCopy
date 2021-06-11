#include "TerrainBuilder.h"


ratchet::TerrainBuilder::TerrainBuilder() :
    super(),
    _resource() {
}

ratchet::TerrainBuilder::~TerrainBuilder() {
}

void ratchet::TerrainBuilder::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::TerrainBuilder::Release(void) {
    super::Release();
    _resource.reset();
}

void ratchet::TerrainBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto temp = std::any_cast<std::shared_ptr<ratchet::Actor>>(shared_this);
    auto ptr = std::dynamic_pointer_cast<ratchet::Terrain>(temp);
    ptr->SetResourceManager(_resource);
}