#include "EventManager.h"


rachet::EventManager::EventManager() :
    _events() {
}

rachet::EventManager::~EventManager() {
}

void rachet::EventManager::OnNotify(const char* type, const std::shared_ptr<rachet::Event>& ptr) {
    if (type == "AddRequest") {
    } // if
    else if (type == "DeleteRequest") {
        ptr->GetSubject()->RemoveObserver(shared_from_this());
        ut::EraseRemove(_events, ptr);
    } // else if
}

bool rachet::EventManager::InitializeGameEvent(void) {
    _events.clear();
    return true;
}

bool rachet::EventManager::Update(float delta_time) {
    for (auto& e : _events) {
        e->Update(delta_time);
    } // for
    return true;
}

bool rachet::EventManager::Release(void) {
    _events.clear();
    return true;
}