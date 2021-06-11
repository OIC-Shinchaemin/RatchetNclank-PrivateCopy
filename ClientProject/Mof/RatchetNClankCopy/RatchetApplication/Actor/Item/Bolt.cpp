#include "Bolt.h"

#include "../../Component/Item/BoltComponent.h"


ratchet::actor::item::Bolt::Bolt() :
    super(),
    _money_subject(){
}

ratchet::actor::item::Bolt::~Bolt() {
}

base::core::Observable<int>* ratchet::actor::item::Bolt::GetMoneySubject(void) {
    return &this->_money_subject;
}

void ratchet::actor::item::Bolt::End(void) {
    _money_subject.Notify(1);
    super::End();
}

bool ratchet::actor::item::Bolt::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);
    auto bolt_param = dynamic_cast<ratchet::actor::item::Bolt::Param*>(param);
    
    _init_speed = bolt_param->speed;
    _init_angle = bolt_param->angle;
    
    super::GetComponent<ratchet::BoltComponent>()->SetActorParam(*bolt_param);
    return true;
}