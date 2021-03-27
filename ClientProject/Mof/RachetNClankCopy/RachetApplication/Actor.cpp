#include "Actor.h"

my::Actor::Actor() :
    _transform() {
}

my::Actor::~Actor() {
}


void my::Actor::SetPosition(Mof::CVector3 position) {
    this->_transform.position = position;
}

void my::Actor::SetRotate(Mof::CVector3 rotate) {
    this->_transform.rotate = rotate;
}

void my::Actor::SetScale(Mof::CVector3 scale) {
    this->_transform.scale = scale;
}

std::string my::Actor::GetName(void) const {
    return std::string();
}

Mof::CVector3 my::Actor::GetPosition(void) const {
    return this->_transform.position;
}

Mof::CVector3 my::Actor::GetRotate(void) const {
    return this->_transform.rotate;
}

Mof::CVector3 my::Actor::GetScale(void) const {
    return this->_transform.scale;
}

bool my::Actor::Initialize(const def::Transform& transform) {
    return true;
}

bool my::Actor::Input(void) {
    return true;
}

bool my::Actor::Update(float delta_time) {
    return true;
}

bool my::Actor::Render(void) {
    return true;
}

bool my::Actor::Release(void) {
    return true;
}