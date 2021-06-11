#include "Bolt.h"

#include "../../Component/Item/BoltComponent.h"


rachet::Bolt::Bolt() :
    super(),
    _money_subject(){
}

rachet::Bolt::~Bolt() {
}

base::core::Observable<int>* rachet::Bolt::GetMoneySubject(void) {
    return &this->_money_subject;
}

void rachet::Bolt::End(void) {
    _money_subject.Notify(1);
    super::End();
}

bool rachet::Bolt::Initialize(rachet::Actor::Param* param) {
    super::Initialize(param);
    auto bolt_param = dynamic_cast<rachet::Bolt::Param*>(param);
    
    _init_speed = bolt_param->speed;
    _init_angle = bolt_param->angle;
    
    super::GetComponent<rachet::BoltComponent>()->SetActorParam(*bolt_param);
    return true;
}