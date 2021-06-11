#include "Event.h"


rachet::Event::Event() {
}

rachet::Event::~Event() {
}

base::core::Observable<const char*, const std::shared_ptr<rachet::Event>&>* rachet::Event::GetSubject(void) {
    return &this->_subject;
}

bool rachet::Event::Initialize(void) {
    return false;
}

bool rachet::Event::Update(float delta_time) {
    return true;
}