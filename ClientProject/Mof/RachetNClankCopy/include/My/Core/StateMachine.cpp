#include "StateMachine.h"


const char* my::StateMachine::GetCurrentStateName(void) const {
    return _current_state->GetName();
}

void my::StateMachine::RegisterState(const std::shared_ptr<my::State>& ptr) {
    _status.emplace(ptr->GetName(), ptr);
}

void my::StateMachine::ChangeState(const std::string& name) {
//    _stack.clear();
    // Œ»Ý‚Ìó‘Ô‚ðI—¹‚·‚é
    if (_current_state) {
        _current_state->Exit();
    } // if
    // ó‘Ô‚Ì•ÏX
    auto it = _status.find(name);
    if (it != _status.end()) {
        _current_state = it->second;
        _current_state->Enter();
    } // if
    else {
        _current_state = nullptr;
    } // else
}

/*
void my::StateMachine::PushState(const std::string& name) {
    _stack.push_back(_status.at(name));
    _current_state = _stack.back();
}

void my::StateMachine::PopState(void) {
    _stack.pop_back();
}
*/

void my::StateMachine::Update(float delta_time) {
    if (!_current_state) {
        return;
    } // if
    _current_state->Update(delta_time);
}

void my::StateMachine::Release(void) {
    _current_state.reset();
    for (auto& state : _status) {
        state.second.reset();
    } // for
    _status.clear();
}

void my::StateMachine::DebugRender(void) {
    if (!_current_state) {
        return;
    } // if
    _current_state->DebugRender();
}