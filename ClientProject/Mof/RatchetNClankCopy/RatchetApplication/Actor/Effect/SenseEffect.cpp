#include "SenseEffect.h"

#include "../../Component/SenseEffect/SenseEffectComponent.h"


ratchet::actor::effect::SenseEffect::SenseEffect() :
    super() {
}

ratchet::actor::effect::SenseEffect::~SenseEffect() {
}

void ratchet::actor::effect::SenseEffect::OnNotify(const FindEnemyMessage& message) {
    super::Activate();
    auto type_com = super::GetComponent<component::effect::SenseEffectComponent>();
    type_com->TimerStart();
}

bool ratchet::actor::effect::SenseEffect::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::effect::SenseEffect::Render(void) {
    super::Render();
    return true;
}