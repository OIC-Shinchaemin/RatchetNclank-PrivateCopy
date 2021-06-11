#include "ActorBuilder.h"


ratchet::ActorBuilder::ActorBuilder() :
    _param(),
    _components() {
}

ratchet::ActorBuilder::~ActorBuilder() {
}

void ratchet::ActorBuilder::SetActorParam(const ratchet::Actor::Param& param) {
    this->_param = param;
}

void ratchet::ActorBuilder::AddComponent(const std::shared_ptr<ratchet::Component>& component) {
    _components.push_back(component);
}

void ratchet::ActorBuilder::Release(void) {
    _components.clear();
}

void ratchet::ActorBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<ratchet::Actor>>(shared_this);
   
    ptr->CloneToComponents(_components);
    ptr->SetName(_param.name.c_str());
    ptr->SetPosition(_param.transform.position);
    ptr->SetRotate(_param.transform.rotate);
    ptr->SetScale(_param.transform.scale);
}