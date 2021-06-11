#include "EventManager.h"


ratchet::event::EventManager::EventManager() :
    _events() {
}

ratchet::event::EventManager::~EventManager() {
}

void ratchet::event::EventManager::OnNotify(const char* type, const std::shared_ptr<ratchet::event::Event>& ptr) {
    if (type == "AddRequest") {
    } // if
    else if (type == "DeleteRequest") {
        ptr->GetSubject()->RemoveObserver(shared_from_this());
        ut::EraseRemove(_events, ptr);
    } // else if
}

bool ratchet::event::EventManager::InitializeGameEvent(void) {
    _events.clear();
    return true;
}

bool ratchet::event::EventManager::Update(float delta_time) {
    for (auto& e : _events) {
        e->Update(delta_time);
    } // for
    return true;
}

bool ratchet::event::EventManager::Release(void) {
    _events.clear();
    return true;
}