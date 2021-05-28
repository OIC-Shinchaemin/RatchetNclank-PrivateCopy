#include "Event.h"


my::Event::Event() {
}

my::Event::~Event() {
}

my::Observable<const char*, const std::shared_ptr<my::Event>&>* my::Event::GetSubject(void) {
    return &this->_subject;
}

bool my::Event::Initialize(void) {
    return false;
}

bool my::Event::Update(float delta_time) {
    return true;
}