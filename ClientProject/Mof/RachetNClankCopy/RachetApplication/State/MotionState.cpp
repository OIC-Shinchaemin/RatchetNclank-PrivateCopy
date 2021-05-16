#include "MotionState.h"


state::MotionState::MotionState() :
    _param(),
    _motion_com() {
}

state::MotionState::~MotionState() {
}

void state::MotionState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    _motion_com = ptr->GetComponent<my::MotionComponent>();
}

void state::MotionState::SetParam(const state::MotionState::Param& param) {
    _param = param;
}

const char* state::MotionState::GetName(void) const {
    return _param.state_name;
}

void state::MotionState::Update(float delta_time) {
}

void state::MotionState::Enter(void) {
    if (auto motion_com = _motion_com.lock()) {
        motion_com->ChangeMotion(
            _param.motion_type,
            _param.motion_speed,
            _param.motion_loop,
            _param.motion_same);
    } // if
}

void state::MotionState::Exit(void) {
}