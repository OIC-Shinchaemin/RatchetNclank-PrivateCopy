#include "NanotechItem.h"

//#include "../../Component/Item/NanotechItemComponent.h"


my::NanotechItem::NanotechItem() :
    super()
    //,
    //_money_subject(){
{  
}

my::NanotechItem::~NanotechItem() {
}
/*
my::Observable<int>* my::NanotechItem::GetMoneySubject(void) {
    return &this->_money_subject;
}
*/
void my::NanotechItem::End(void) {
    //_money_subject.Notify(1);
    super::End();
}

bool my::NanotechItem::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    auto NanotechItem_param = dynamic_cast<my::NanotechItem::Param*>(param);
    
    _init_speed = NanotechItem_param->speed;
    _init_angle = NanotechItem_param->angle;
    
    //super::GetComponent<my::NanotechItemComponent>()->SetActorParam(*NanotechItem_param);
    return true;
}