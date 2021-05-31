#include "Bolt.h"

#include "../../Component/Item/BoltComponent.h"


my::Bolt::Bolt() :
    super() {
}

my::Bolt::~Bolt() {
}

bool my::Bolt::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    auto bolt_param = dynamic_cast<my::Bolt::Param*>(param);
    
    _init_speed = bolt_param->speed;
    _init_angle = bolt_param->angle;
    
    super::GetComponent<my::BoltComponent>()->SetActorParam(*bolt_param);
    return true;
}