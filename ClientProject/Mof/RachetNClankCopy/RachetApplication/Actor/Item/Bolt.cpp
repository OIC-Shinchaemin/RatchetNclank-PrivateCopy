#include "Bolt.h"

#include "../../Component/Item/BoltComponent.h"


my::Bolt::Bolt() :
    super(),
    _money_subject(){
}

my::Bolt::~Bolt() {
}

base::core::Observable<int>* my::Bolt::GetMoneySubject(void) {
    return &this->_money_subject;
}

void my::Bolt::End(void) {
    _money_subject.Notify(1);
    super::End();
}

bool my::Bolt::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    auto bolt_param = dynamic_cast<my::Bolt::Param*>(param);
    
    _init_speed = bolt_param->speed;
    _init_angle = bolt_param->angle;
    
    super::GetComponent<my::BoltComponent>()->SetActorParam(*bolt_param);
    return true;
}