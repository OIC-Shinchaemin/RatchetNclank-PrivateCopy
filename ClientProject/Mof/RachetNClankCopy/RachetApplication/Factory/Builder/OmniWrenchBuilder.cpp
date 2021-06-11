#include "OmniWrenchBuilder.h"


rachet::OmniWrenchBuilder::OmniWrenchBuilder() :
    super() {
}

rachet::OmniWrenchBuilder::~OmniWrenchBuilder() {
}
/*
void rachet::OmniWrenchBuilder::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    this->_resource = ptr;
}
*/

void rachet::OmniWrenchBuilder::Release(void) {
    super::Release();
    //_resource.reset();
}

void rachet::OmniWrenchBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto temp = std::any_cast<std::shared_ptr<rachet::Actor>>(shared_this);
    //auto ptr = std::dynamic_pointer_cast<rachet::OmniWrench>(temp);
    //ptr->SetResourceManager(_resource);
}