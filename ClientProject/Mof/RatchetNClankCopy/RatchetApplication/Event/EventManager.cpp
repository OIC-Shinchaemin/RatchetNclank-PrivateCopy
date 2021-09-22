#include "EventManager.h"


ratchet::event::EventManager::EventManager() :
	_events(),
	_created_events(),
	_delete_events() {
}

ratchet::event::EventManager::~EventManager() {
}

void ratchet::event::EventManager::OnNotify(const char* type, const std::shared_ptr<ratchet::event::Event>& ptr) {
	if (type == "AddRequest") {
		ptr->GetSubject()->AddObserver(shared_from_this());
		_created_events.push_back(ptr);
	} // if
	else if (type == "DeleteRequest") {
		ptr->GetSubject()->RemoveObserver(shared_from_this());
		_delete_events.push_back(ptr);
	} // else if
}

bool ratchet::event::EventManager::InitializeGameEvent(void) {
	_events.clear();
	_created_events.clear();
	_delete_events.clear();
	return true;
}

bool ratchet::event::EventManager::Update(float delta_time) {
	for (auto& e: _created_events) {
		_events.push_back(e);
	} // for
	_created_events.clear();
	for (auto& e : _delete_events) {
		ut::SwapPopback(_events, e);
	} // for
	_delete_events.clear();

	for (auto& e : _events) {
		e->Update(delta_time);
	} // for
	return true;
}

bool ratchet::event::EventManager::Release(void) {
	_created_events.clear();
	_delete_events.clear();
	_events.clear();
	return true;
}