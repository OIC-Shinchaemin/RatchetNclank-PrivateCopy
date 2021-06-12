#include "MotionState.h"


ratchet::state::MotionState::MotionState() :
    _param(),
    _motion_com() {
}

ratchet::state::MotionState::~MotionState() {
}

void ratchet::state::MotionState::SetActor(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    _motion_com = ptr->GetComponent<ratchet::component::MotionComponent>();
}

void ratchet::state::MotionState::SetParam(const ratchet::state::MotionState::Param& param) {
    _param = param;
}

const char* ratchet::state::MotionState::GetName(void) const {
    return _param.state_name;
}

void ratchet::state::MotionState::Update(float delta_time) {
}

void ratchet::state::MotionState::Enter(void) {
    if (auto motion_com = _motion_com.lock()) {
        motion_com->ChangeMotion(
            _param.motion_type,
            _param.motion_speed,
            _param.motion_loop,
            _param.motion_same);
    } // if
}

void ratchet::state::MotionState::Exit(void) {
}