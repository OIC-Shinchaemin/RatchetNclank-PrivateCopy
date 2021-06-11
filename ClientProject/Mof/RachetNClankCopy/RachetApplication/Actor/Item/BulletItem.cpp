#include "BulletItem.h"

#include "../../Component/Item/BulletItem/BulletItemComponent.h"


rachet::BulletItem::BulletItem() :
    super()
    //,
    //_money_subject(){
{  
}

rachet::BulletItem::~BulletItem() {
    _weapon_system_subject.Clear();
}

std::string rachet::BulletItem::GetTypeName(rachet::BulletItem::Type type) const {
    switch (_item_type) 	{
        case rachet::BulletItem::Type::BombGlove:
            return std::string("BombGlove");
        case rachet::BulletItem::Type::Pyrocitor:
            return std::string("Pyrocitor");
        case rachet::BulletItem::Type::Blaster:
            return std::string("Blaster");
        default:
            break;
    }
    return std::string();
}
/*
base::core::Observable<int>* rachet::BulletItem::GetMoneySubject(void) {
    return &this->_money_subject;
}
*/
base::core::Observable<const rachet::ChargeInfo&>* rachet::BulletItem::GetWeaponSystemSubject(void) {
    return &this->_weapon_system_subject;
}
void rachet::BulletItem::End(void) {
    //_money_subject.Notify(1);
    auto info = rachet::ChargeInfo();
    info.size = _item_count;
    info.type = this->GetTypeName(_item_type);
    _weapon_system_subject.Notify(info);
    super::End();
}

bool rachet::BulletItem::Initialize(rachet::Actor::Param* param) {
    auto bulletitem_param = dynamic_cast<rachet::BulletItem::Param*>(param);
    
    _init_speed = bulletitem_param->speed;
    _init_angle = bulletitem_param->angle;
    _item_count = bulletitem_param->count;
    _item_type = bulletitem_param->type;

    super::GetComponent<rachet::BulletItemComponent>()->SetActorParam(*bulletitem_param);
    
    super::Initialize(param);
    return true;
}