#include "ActorBuilder.h"


my::ActorBuilder::ActorBuilder() :
    _param(),
    _components() {
}

my::ActorBuilder::~ActorBuilder() {
}

void my::ActorBuilder::Release(void) {
    _components.clear();
}

void my::ActorBuilder::SetActorParam(const my::Actor::Param& param) {
    this->_param = param;
}

void my::ActorBuilder::AddComponent(const std::shared_ptr<my::Component>& component) {
    _components.push_back(component);
}

void my::ActorBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<my::Actor>>(shared_this);
   
    ptr->CloneToComponents(_components);
    ptr->SetName(_param.name.c_str());
    ptr->SetPosition(_param.transform.position);
    ptr->SetRotate(_param.transform.rotate);
    ptr->SetScale(_param.transform.scale);
}