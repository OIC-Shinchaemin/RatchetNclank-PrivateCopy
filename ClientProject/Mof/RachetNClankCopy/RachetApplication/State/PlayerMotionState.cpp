#include "PlayerMotionState.h"


bool state::PlayerMotionState::ChangeMotion(Player::MotionType type) {
    if (auto motion_com = _motion_com.lock()) {
        return motion_com->ChangeMotion(type, _motion_speed, _motion_loop, _motion_same);
    } // if
    return false;
}

bool state::PlayerMotionState::ChangeState(const char* next) const {
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(next);
        return true;
    } // if
    return false;
}

state::PlayerMotionState::PlayerMotionState() :
    _motion_speed(1.0f),
    _motion_loop(true),
    _motion_same(true),
    _motion_com(),
    _motion_state_com(){
}

state::PlayerMotionState::~PlayerMotionState() {
}

void state::PlayerMotionState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    _motion_com = ptr->GetComponent<my::MotionComponent>();
    _motion_state_com = ptr->GetComponent<my::MotionStateComponent>();
}