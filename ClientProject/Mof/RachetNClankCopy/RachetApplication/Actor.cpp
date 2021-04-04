#include "Actor.h"

#include "My/Core/Math.h"


Mof::CVector3 my::Actor::UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity) {
    float sleep_threshold = 0.01f;
    if (sleep_threshold < velocity.Length()) {
        rotate += velocity * delta_time;
    } // if

    if (math::kTwoPi <= rotate.y) {
        rotate.y -= math::kTwoPi;
    } // if
    else if (rotate.y <= 0.0f) {
        rotate.y += math::kTwoPi;
    } // else if
    return rotate;
}

Mof::CVector3 my::Actor::UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity) {
    float sleep_threshold = 0.001f;

    if (sleep_threshold < velocity.Length()) {
        position += velocity * delta_time;
    } // if
    return position;
}

my::Actor::Actor() :
    _state(my::ActorState::Active),
    _param(),
    _collision_objects() {
}

my::Actor::~Actor() {
}

void my::Actor::SetPosition(Mof::CVector3 position) {
    this->_param.transform.position = position;
}

void my::Actor::SetRotate(Mof::CVector3 rotate) {
    this->_param.transform.rotate = rotate;
}

void my::Actor::SetScale(Mof::CVector3 scale) {
    this->_param.transform.scale = scale;
}

std::string my::Actor::GetName(void) const {
    return std::string();
}

Mof::CVector3 my::Actor::GetPosition(void) const {
    return this->_param.transform.position;
}

Mof::CVector3 my::Actor::GetRotate(void) const {
    return this->_param.transform.rotate;
}

Mof::CVector3 my::Actor::GetScale(void) const {
    return this->_param.transform.scale;
}

my::ActorState my::Actor::GetState(void) const {
    return this->_state;
}

const std::vector<std::shared_ptr<my::CollisionObject>>& my::Actor::GetCollisionObjects(void) const {
    return this->_collision_objects;
}

void my::Actor::End(void) {
    this->_state = my::ActorState::End;
    Observable::Notify("DeleteRequest", shared_from_this());
}

bool my::Actor::Initialize(my::Actor::Param* param) {
    _state = my::ActorState::Active;
    _param.transform = param->transform;
    _param.init_transform = _param.transform;
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
    _collision_objects.clear();
    return true;
}

void my::Actor::RenderDebug(void) {
}