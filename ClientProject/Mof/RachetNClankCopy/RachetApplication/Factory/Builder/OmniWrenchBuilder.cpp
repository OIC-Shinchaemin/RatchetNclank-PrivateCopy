#include "OmniWrenchBuilder.h"


my::OmniWrenchBuilder::OmniWrenchBuilder() :
    super() {
}

my::OmniWrenchBuilder::~OmniWrenchBuilder() {
}
/*
void my::OmniWrenchBuilder::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}
*/

void my::OmniWrenchBuilder::Release(void) {
    super::Release();
    //_resource.reset();
}

void my::OmniWrenchBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto temp = std::any_cast<std::shared_ptr<my::Actor>>(shared_this);
    //auto ptr = std::dynamic_pointer_cast<my::OmniWrench>(temp);
    //ptr->SetResourceManager(_resource);
}