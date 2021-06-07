#include "BulletItem.h"

#include "../../Component/Item/BulletItem/BulletItemComponent.h"


my::BulletItem::BulletItem() :
    super()
    //,
    //_money_subject(){
{  
}

my::BulletItem::~BulletItem() {
}
/*
my::Observable<int>* my::BulletItem::GetMoneySubject(void) {
    return &this->_money_subject;
}
*/
void my::BulletItem::End(void) {
    //_money_subject.Notify(1);
    super::End();
}

bool my::BulletItem::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    auto bulletitem_param = dynamic_cast<my::BulletItem::Param*>(param);
    
    _init_speed = bulletitem_param->speed;
    _init_angle = bulletitem_param->angle;
    
    super::GetComponent<my::BulletItemComponent>()->SetActorParam(*bulletitem_param);
    return true;
}