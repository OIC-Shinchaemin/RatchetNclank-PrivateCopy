#include "Event.h"


ratchet::event::Event::Event() {
}

ratchet::event::Event::~Event() {
}

base::core::Observable<const char*, const std::shared_ptr<ratchet::event::Event>&>* ratchet::event::Event::GetSubject(void) {
    return &this->_subject;
}

bool ratchet::event::Event::Initialize(void) {
    return false;
}

bool ratchet::event::Event::Update(float delta_time) {
    return true;
}