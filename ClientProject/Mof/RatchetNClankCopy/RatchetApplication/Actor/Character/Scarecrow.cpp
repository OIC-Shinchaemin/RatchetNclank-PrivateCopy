#include "Scarecrow.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::character::Scarecrow::Scarecrow() :
	super() {
	super::SetTag("Enemy");
}

ratchet::actor::character::Scarecrow::~Scarecrow() {
}

void ratchet::actor::character::Scarecrow::SetEffectEmitter(const std::shared_ptr<ratchet::effect::EffectEmitter>& ptr) {
	this->_effect_emitter = ptr;
}

void ratchet::actor::character::Scarecrow::SetStarEffectEmitter(const std::shared_ptr<ratchet::effect::EffectEmitter>& ptr) {
	this->_star_effect_emitter = ptr;
}

std::shared_ptr<ratchet::effect::EffectEmitter> ratchet::actor::character::Scarecrow::GetEffectEmitter(void) const {
	return this->_effect_emitter;
}

std::shared_ptr<ratchet::effect::EffectEmitter> ratchet::actor::character::Scarecrow::GetStarEffectEmitter(void) const {
	return this->_star_effect_emitter;
}

void ratchet::actor::character::Scarecrow::End(void) {
	super::End();

	auto message = ScarecrowEndMessage();
	message.end = true;
	message.ptr = shared_from_this();
	_end_message_subject.Notify(message);
}

bool ratchet::actor::character::Scarecrow::Initialize(ratchet::actor::Actor::Param* param) {
	super::Initialize(param);

	auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
	velocity->Inactivate();
	velocity->SetUseGravity(false);
	return true;
}

bool ratchet::actor::character::Scarecrow::Update(float delta_time) {
	super::Update(delta_time);
	return true;
}

bool ratchet::actor::character::Scarecrow::Render(void) {
	super::Render();
	return true;
}