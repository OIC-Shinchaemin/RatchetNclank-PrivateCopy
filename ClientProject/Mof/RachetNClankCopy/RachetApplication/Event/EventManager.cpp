#include "EventManager.h"


my::EventManager::EventManager() :
    _events() {
}

my::EventManager::~EventManager() {
}

void my::EventManager::OnNotify(const char* type, const std::shared_ptr<my::Event>& ptr) {
    if (type == "AddRequest") {
    } // if
    else if (type == "DeleteRequest") {
        ptr->GetSubject()->RemoveObserver(shared_from_this());
        ut::EraseRemove(_events, ptr);
    } // else if
}

bool my::EventManager::InitializeGameEvent(void) {
    _events.clear();
    return true;
}

bool my::EventManager::UpdateGameEvent(float delta_time) {
    for (auto& e : _events) {
        e->Update(delta_time);
    } // for
    return true;
}

bool my::EventManager::Release(void) {
    _events.clear();
    return true;
}