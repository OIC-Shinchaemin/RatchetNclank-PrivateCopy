#include "Actor.h"

my::Actor::Actor() :
    _state(my::ActorState::Active),
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

my::ActorState my::Actor::GetState(void) const {
    return this->_state;
}

void my::Actor::End(void) {
    this->_state = my::ActorState::End;
    Observable::Notify("DeleteRequest",shared_from_this());
}

bool my::Actor::Initialize(const def::Transform& transform) {
    _state = my::ActorState::Active;
    _transform = transform;
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

void my::Actor::RenderDebug(void) {
}