#include "Effect.h"


ratchet::effect::Effect::Effect() :
	_enable(false),
	_life_timer(),
	_initialize_param(),
	_basic_param(),
	_update_param(),
	_environment_param() {
}

ratchet::effect::Effect::~Effect() {
}

bool ratchet::effect::Effect::IsEnable(void) const {
	return this->_enable;
}

const ratchet::effect::Effect::BasicParam& ratchet::effect::Effect::GetBasicParam(void) const {
	return this->_basic_param;
}

bool ratchet::effect::Effect::Initialize(void) {
	_basic_param = _initialize_param.value();
	_enable = true;
	_life_timer.Initialize(_basic_param.life_duration, false, true);
	return true;
}

bool ratchet::effect::Effect::Update(float delta_time) {
	if (_life_timer.Tick(delta_time)) {
		this->_enable = false;
		return true;
	} // if
	
	_update_param += _environment_param;

	_basic_param += _environment_param;

	_basic_param += _update_param;
	return false;
}

bool ratchet::effect::Effect::Render(void) {
	return true; 
}

void ratchet::effect::Effect::Start(const ratchet::effect::Effect::Info& info) {
	_initialize_param = info.init_param;
	_update_param = info.update_param;
	_environment_param = info.environment_param;
	this->Initialize();
}