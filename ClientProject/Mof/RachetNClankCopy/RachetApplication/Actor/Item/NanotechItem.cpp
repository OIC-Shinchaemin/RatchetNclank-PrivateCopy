#include "NanotechItem.h"

#include "../../Component/Item/NanotechItem/NanotechItemComponent.h"


rachet::NanotechItem::NanotechItem() :
    super()
    //,
    //_money_subject(){
{  
}

rachet::NanotechItem::~NanotechItem() {
}
/*
base::core::Observable<int>* rachet::NanotechItem::GetMoneySubject(void) {
    return &this->_money_subject;
}
*/
void rachet::NanotechItem::End(void) {
    //_money_subject.Notify(1);
    super::End();
}

bool rachet::NanotechItem::Initialize(rachet::Actor::Param* param) {
    super::Initialize(param);
    auto nanotechitem_param = dynamic_cast<rachet::NanotechItem::Param*>(param);
    
    _init_speed = nanotechitem_param ->speed;
    _init_angle = nanotechitem_param ->angle;
    
    super::GetComponent<rachet::NanotechItemComponent>()->SetActorParam(*nanotechitem_param);
    return true;
}