#include "MotionState.h"


bool state::MotionState::ChangeMotion(my::Player::MotionType type) {
    if (auto motion_com = _motion_com.lock()) {
        return motion_com->ChangeMotion(type, _motion_speed, _motion_loop, _motion_same);
    } // if
    return false;
}

state::MotionState::MotionState() :
    _motion_speed(1.0f),
    _motion_loop(true),
    _motion_same(true),
    _motion_com() {

    _motion_loop = false;
    _motion_same = false;
}

state::MotionState::~MotionState() {
}

void state::MotionState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    _motion_com = ptr->GetComponent<my::MotionComponent>();
}

const char* state::MotionState::GetName(void) const {
    //return state::PlayerMotionStateType::kPlayerMotionDoubleJumpState.c_str();
    return "";
}

void state::MotionState::Update(float delta_time) {
}

void state::MotionState::Enter(void) {
    this->ChangeMotion(my::Player::MotionType::DoubleJump);
}

void state::MotionState::Exit(void) {
}
