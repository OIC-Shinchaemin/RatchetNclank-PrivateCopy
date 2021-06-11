#include "BulletItem.h"

#include "../../Component/Item/BulletItem/BulletItemComponent.h"


ratchet::BulletItem::BulletItem() :
    super()
    //,
    //_money_subject(){
{  
}

ratchet::BulletItem::~BulletItem() {
    _weapon_system_subject.Clear();
}

std::string ratchet::BulletItem::GetTypeName(ratchet::BulletItem::Type type) const {
    switch (_item_type) 	{
        case ratchet::BulletItem::Type::BombGlove:
            return std::string("BombGlove");
        case ratchet::BulletItem::Type::Pyrocitor:
            return std::string("Pyrocitor");
        case ratchet::BulletItem::Type::Blaster:
            return std::string("Blaster");
        default:
            break;
    }
    return std::string();
}
/*
base::core::Observable<int>* ratchet::BulletItem::GetMoneySubject(void) {
    return &this->_money_subject;
}
*/
base::core::Observable<const ratchet::ChargeInfo&>* ratchet::BulletItem::GetWeaponSystemSubject(void) {
    return &this->_weapon_system_subject;
}
void ratchet::BulletItem::End(void) {
    //_money_subject.Notify(1);
    auto info = ratchet::ChargeInfo();
    info.size = _item_count;
    info.type = this->GetTypeName(_item_type);
    _weapon_system_subject.Notify(info);
    super::End();
}

bool ratchet::BulletItem::Initialize(ratchet::Actor::Param* param) {
    auto bulletitem_param = dynamic_cast<ratchet::BulletItem::Param*>(param);
    
    _init_speed = bulletitem_param->speed;
    _init_angle = bulletitem_param->angle;
    _item_count = bulletitem_param->count;
    _item_type = bulletitem_param->type;

    super::GetComponent<ratchet::BulletItemComponent>()->SetActorParam(*bulletitem_param);
    
    super::Initialize(param);
    return true;
}