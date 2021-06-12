#include "NanotechItem.h"

#include "../../Component/Item/NanotechItem/NanotechItemComponent.h"


ratchet::actor::item::NanotechItem::NanotechItem() :
    super() {  
}

ratchet::actor::item::NanotechItem::~NanotechItem() {
}

void ratchet::actor::item::NanotechItem::End(void) {
    super::End();
}

bool ratchet::actor::item::NanotechItem::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);
    auto nanotechitem_param = dynamic_cast<ratchet::actor::item::NanotechItem::Param*>(param);
    
    _init_speed = nanotechitem_param ->speed;
    _init_angle = nanotechitem_param ->angle;
    
    super::GetComponent<ratchet::component::item::nanotechitem::NanotechItemComponent>()->SetActorParam(*nanotechitem_param);
    return true;
}