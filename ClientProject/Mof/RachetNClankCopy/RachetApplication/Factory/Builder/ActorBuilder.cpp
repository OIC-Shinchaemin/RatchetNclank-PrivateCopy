#include "ActorBuilder.h"


rachet::ActorBuilder::ActorBuilder() :
    _param(),
    _components() {
}

rachet::ActorBuilder::~ActorBuilder() {
}

void rachet::ActorBuilder::SetActorParam(const rachet::Actor::Param& param) {
    this->_param = param;
}

void rachet::ActorBuilder::AddComponent(const std::shared_ptr<rachet::Component>& component) {
    _components.push_back(component);
}

void rachet::ActorBuilder::Release(void) {
    _components.clear();
}

void rachet::ActorBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<rachet::Actor>>(shared_this);
   
    ptr->CloneToComponents(_components);
    ptr->SetName(_param.name.c_str());
    ptr->SetPosition(_param.transform.position);
    ptr->SetRotate(_param.transform.rotate);
    ptr->SetScale(_param.transform.scale);
}