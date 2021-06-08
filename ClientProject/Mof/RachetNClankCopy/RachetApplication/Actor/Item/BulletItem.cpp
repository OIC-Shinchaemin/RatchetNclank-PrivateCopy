#include "BulletItem.h"

#include "../../Component/Item/BulletItem/BulletItemComponent.h"


my::BulletItem::BulletItem() :
    super()
    //,
    //_money_subject(){
{  
}

my::BulletItem::~BulletItem() {
    _weapon_system_subject.Clear();
}

std::string my::BulletItem::GetTypeName(my::BulletItem::Type type) const {
    switch (_item_type) 	{
        case my::BulletItem::Type::BombGlove:
            return std::string("BombGlove");
        case my::BulletItem::Type::Pyrocitor:
            return std::string("Pyrocitor");
        case my::BulletItem::Type::Blaster:
            return std::string("Blaster");
        default:
            break;
    }
    return std::string();
}
/*
my::Observable<int>* my::BulletItem::GetMoneySubject(void) {
    return &this->_money_subject;
}
*/
my::Observable<const my::ChargeInfo&>* my::BulletItem::GetWeaponSystemSubject(void) {
    return &this->_weapon_system_subject;
}
void my::BulletItem::End(void) {
    //_money_subject.Notify(1);
    auto info = my::ChargeInfo();
    info.size = _item_count;
    info.type = this->GetTypeName(_item_type);
    _weapon_system_subject.Notify(info);
    super::End();
}

bool my::BulletItem::Initialize(my::Actor::Param* param) {
    auto bulletitem_param = dynamic_cast<my::BulletItem::Param*>(param);
    
    _init_speed = bulletitem_param->speed;
    _init_angle = bulletitem_param->angle;
    _item_count = bulletitem_param->count;
    _item_type = bulletitem_param->type;

    super::GetComponent<my::BulletItemComponent>()->SetActorParam(*bulletitem_param);
    
    super::Initialize(param);
    return true;
}