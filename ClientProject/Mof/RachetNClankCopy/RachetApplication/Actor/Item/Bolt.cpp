#include "Bolt.h"

#include "../../Component/Item/BoltComponent.h"


ratchet::Bolt::Bolt() :
    super(),
    _money_subject(){
}

ratchet::Bolt::~Bolt() {
}

base::core::Observable<int>* ratchet::Bolt::GetMoneySubject(void) {
    return &this->_money_subject;
}

void ratchet::Bolt::End(void) {
    _money_subject.Notify(1);
    super::End();
}

bool ratchet::Bolt::Initialize(ratchet::Actor::Param* param) {
    super::Initialize(param);
    auto bolt_param = dynamic_cast<ratchet::Bolt::Param*>(param);
    
    _init_speed = bolt_param->speed;
    _init_angle = bolt_param->angle;
    
    super::GetComponent<ratchet::BoltComponent>()->SetActorParam(*bolt_param);
    return true;
}