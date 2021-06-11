#include "OmniWrenchBuilder.h"


ratchet::OmniWrenchBuilder::OmniWrenchBuilder() :
    super() {
}

ratchet::OmniWrenchBuilder::~OmniWrenchBuilder() {
}
/*
void ratchet::OmniWrenchBuilder::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}
*/

void ratchet::OmniWrenchBuilder::Release(void) {
    super::Release();
    //_resource.reset();
}

void ratchet::OmniWrenchBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto temp = std::any_cast<std::shared_ptr<ratchet::Actor>>(shared_this);
    //auto ptr = std::dynamic_pointer_cast<ratchet::OmniWrench>(temp);
    //ptr->SetResourceManager(_resource);
}