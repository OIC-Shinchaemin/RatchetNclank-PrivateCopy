#include "EffectPool.h"


ratchet::effect::EffectPool::EffectPool(const ratchet::effect::EffectPoolCreateInfo& info) :
	_effect_type_path(info.path),
	_effects(info.pool_count) {
}

ratchet::effect::EffectPool::~EffectPool() {
}

void ratchet::effect::EffectPool::SetResourcePath(const std::string& path) {
	this->_effect_type_path = path;
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