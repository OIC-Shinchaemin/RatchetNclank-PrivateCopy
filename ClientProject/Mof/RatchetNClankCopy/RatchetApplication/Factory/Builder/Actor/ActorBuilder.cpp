#include "ActorBuilder.h"


ratchet::factory::builder::actor::ActorBuilder::ActorBuilder() :
    _param(),
    _components() {
}

ratchet::factory::builder::actor::ActorBuilder::~ActorBuilder() {
}

void ratchet::factory::builder::actor::ActorBuilder::SetActorParam(const ratchet::actor::Actor::Param& param) {
    this->_param = param;
}

void ratchet::factory::builder::actor::ActorBuilder::AddComponent(const std::shared_ptr<ratchet::component::Component>& component) {
    _components.push_back(component);
}

void ratchet::factory::builder::actor::ActorBuilder::Release(void) {
    _components.clear();
}

void ratchet::factory::builder::actor::ActorBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<ratchet::actor::Actor>>(shared_this);
   
    ptr->CloneToComponents(_components);
    ptr->SetName(_param.name.c_str());
    ptr->SetPosition(_param.transform.position);
    ptr->SetRotate(_param.transform.rotate);
    ptr->SetScale(_param.transform.scale);
}