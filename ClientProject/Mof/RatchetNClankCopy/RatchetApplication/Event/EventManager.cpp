#include "EventManager.h"


ratchet::EventManager::EventManager() :
    _events() {
}

ratchet::EventManager::~EventManager() {
}

void ratchet::EventManager::OnNotify(const char* type, const std::shared_ptr<ratchet::Event>& ptr) {
    if (type == "AddRequest") {
    } // if
    else if (type == "DeleteRequest") {
        ptr->GetSubject()->RemoveObserver(shared_from_this());
        ut::EraseRemove(_events, ptr);
    } // else if
}

bool ratchet::EventManager::InitializeGameEvent(void) {
    _events.clear();
    return true;
}

bool ratchet::EventManager::Update(float delta_time) {
    for (auto& e : _events) {
        e->Update(delta_time);
    } // for
    return true;
}

bool ratchet::EventManager::Release(void) {
    _events.clear();
    return true;
}