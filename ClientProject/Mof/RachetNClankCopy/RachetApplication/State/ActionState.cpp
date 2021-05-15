//#include "ActionState.h"
//
//
//std::shared_ptr<my::Actor> state::ActionState::GetActor(void) const {
//    return this->_actor.lock();
//}
//
//bool state::ActionState::ChangeState(const char* next) const {
//    if (auto state_com = _state_com.lock()) {
//        state_com->ChangeState(next);
//        return true;
//    } // if
//    return false;
//}
//
//state::ActionState::ActionState() :
//    _actor(),
//    _state_com() {
//}
//
//state::ActionState::~ActionState() {
//}
//
//void state::ActionState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
//    _actor = ptr;
//    _state_com = ptr->GetComponent<my::ActionStateComponent>();
//    _action_com = ptr->GetComponent<my::ActionComponent>();
//}
//
//const char* state::ActionState::GetName(void) const {
//    if (auto attack_com = _action_com.lock()) {
//        return attack_com->GetStateType().data();
//    } // if
//    return nullptr;
//}
//
//void state::ActionState::Update(float delta_time) {
//}
//
//void state::ActionState::Enter(void) {
//    if (auto attack_com = _action_com.lock()) {
//        attack_com->Start();
//    } // if
//}
//
//void state::ActionState::Exit(void) {
//    if (auto attack_com = _action_com.lock()) {
//        attack_com->End();
//    } // if
//}