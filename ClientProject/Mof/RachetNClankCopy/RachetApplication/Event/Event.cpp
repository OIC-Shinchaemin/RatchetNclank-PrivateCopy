#include "Event.h"


ratchet::Event::Event() {
}

ratchet::Event::~Event() {
}

base::core::Observable<const char*, const std::shared_ptr<ratchet::Event>&>* ratchet::Event::GetSubject(void) {
    return &this->_subject;
}

bool ratchet::Event::Initialize(void) {
    return false;
}

bool ratchet::Event::Update(float delta_time) {
    return true;
}