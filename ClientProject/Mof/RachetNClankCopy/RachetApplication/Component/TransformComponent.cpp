#include "TransformComponent.h"

#include "VelocityComponent.h"


Mof::CVector3 my::TransformComponent::UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity) {
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

Mof::CVector3 my::TransformComponent::UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity) {
    float sleep_threshold = 0.001f;

    if (sleep_threshold < velocity.Length()) {
        position += velocity * delta_time;
    } // if
    return position;
}

my::TransformComponent::TransformComponent(int priority) :
    super(priority),
    _velocity_com() {
}

my::TransformComponent::TransformComponent(const TransformComponent& obj) :
    super(obj),
    _velocity_com() {
}

my::TransformComponent::~TransformComponent() {
}

std::string my::TransformComponent::GetType(void) const {
    return "TransformComponent";
}

bool my::TransformComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    return true;
}

bool my::TransformComponent::Update(float delta_time) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto owner = super::GetOwner();
        // rotate
        auto rotate = this->UpdateRotate(delta_time, owner->GetRotate(), velocity_com->GetAngularVelocity());
        owner->SetRotate(rotate);
        // position
        auto pos = this->UpdatePosition(delta_time, owner->GetPosition(), velocity_com->GetVelocity());
        owner->SetPosition(pos);
    } // if
    return true;
}

bool my::TransformComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::TransformComponent::Clone(void) {
    return std::make_shared<my::TransformComponent>(*this);
}