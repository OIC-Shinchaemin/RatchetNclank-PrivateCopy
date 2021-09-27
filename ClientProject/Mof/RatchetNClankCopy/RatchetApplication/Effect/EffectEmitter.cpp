#include "EffectEmitter.h"


ratchet::effect::EffectEmitter::EffectEmitter() :
	_pool(),
	_out_target() {
}

ratchet::effect::EffectEmitter::~EffectEmitter() {
}

void ratchet::effect::EffectEmitter::SetPool(ratchet::effect::EffectPool* ptr) {
	this->_pool = ptr;
}

void ratchet::effect::EffectEmitter::SetOutputTarget(std::vector<effect::Effect*>* ptr) {
	this->_out_target = ptr;
}

bool ratchet::effect::EffectEmitter::Emit(const ratchet::effect::Effect::Info& info) {
	auto effect = _pool->Fetch();

	if (!effect) {
		return false;
	} // if
	effect->Start(info);
	_out_target->push_back(effect);
	return true;
}