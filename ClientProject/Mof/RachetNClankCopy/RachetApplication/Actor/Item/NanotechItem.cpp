#include "NanotechItem.h"

#include "../../Component/Item/NanotechItem/NanotechItemComponent.h"


ratchet::NanotechItem::NanotechItem() :
    super()
    //,
    //_money_subject(){
{  
}

ratchet::NanotechItem::~NanotechItem() {
}
/*
base::core::Observable<int>* ratchet::NanotechItem::GetMoneySubject(void) {
    return &this->_money_subject;
}
*/
void ratchet::NanotechItem::End(void) {
    //_money_subject.Notify(1);
    super::End();
}

bool ratchet::NanotechItem::Initialize(ratchet::Actor::Param* param) {
    super::Initialize(param);
    auto nanotechitem_param = dynamic_cast<ratchet::NanotechItem::Param*>(param);
    
    _init_speed = nanotechitem_param ->speed;
    _init_angle = nanotechitem_param ->angle;
    
    super::GetComponent<ratchet::NanotechItemComponent>()->SetActorParam(*nanotechitem_param);
    return true;
}