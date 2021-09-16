#include "EffectPool.h"


ratchet::effect::EffectPool::EffectPool() :
	//_effect_type_path("../Resource/texture/effect/smoke.png"),
	_effect_type_path("../Resource/texture/effect/flash.png"),
	_effects() {
}

ratchet::effect::EffectPool::~EffectPool() {
}

std::string_view ratchet::effect::EffectPool::GetResourcePath(void) const {
	return this->_effect_type_path;
}

ratchet::effect::Effect* ratchet::effect::EffectPool::Fetch(void) {
	for (auto& effect : _effects) {
		if (!effect.IsEnable()) {
			return &effect;
		} // if
	} // for
	return nullptr;
}