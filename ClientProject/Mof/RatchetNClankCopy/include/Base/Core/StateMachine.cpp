#include "StateMachine.h"


const char* base::core::StateMachine::GetCurrentStateName(void) const {
    return _current_state->GetName();
}

bool base::core::StateMachine::EnableState(void) const {
    return _current_state.get();
}

void base::core::StateMachine::RegisterState(const std::shared_ptr<base::core::State>& ptr) {
    _status.emplace(ptr->GetName(), ptr);
}

void base::core::StateMachine::ChangeState(const std::string& name) {
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
void base::core::StateMachine::PushState(const std::string& name) {
    _stack.push_back(_status.at(name));
    _current_state = _stack.back();
}

void base::core::StateMachine::PopState(void) {
    _stack.pop_back();
}
*/

void base::core::StateMachine::Update(float delta_time) {
    if (!_current_state) {
        return;
    } // if
    _current_state->Update(delta_time);
}

void base::core::StateMachine::Release(void) {
    _current_state.reset();
    for (auto& state : _status) {
        state.second.reset();
    } // for
    _status.clear();
}

void base::core::StateMachine::DebugRender(void) {
    if (!_current_state) {
        return;
    } // if
    _current_state->DebugRender();
}