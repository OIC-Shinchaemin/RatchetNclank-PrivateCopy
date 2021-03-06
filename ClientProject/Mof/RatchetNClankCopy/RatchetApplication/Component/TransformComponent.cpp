#include "TransformComponent.h"

#include "VelocityComponent.h"


Mof::CVector3 ratchet::component::TransformComponent::UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity) {
    float sleep_threshold = 0.01f;
    if (sleep_threshold < velocity.Length()) {
        rotate += velocity * delta_time;
    } // if
    /*
    if ((a) >= MOF_MATH_2PI) {
        a -= MOF_MATH_2PI;
    } // if
    else {
        if ((a) < 0.0f) {
            a += MOF_MATH_2PI;
        } // if
        else {
            a;
        } // else
    } // else
    */
    //MOF_NORMALIZE_RADIANANGLE(rotate.y);
    if (math::kTwoPi <= rotate.y) {
        rotate.y -= math::kTwoPi;
    } // if
    else if (rotate.y <= 0.0f) {
        rotate.y += math::kTwoPi;
    } // else
    return rotate;
}

Mof::CVector3 ratchet::component::TransformComponent::UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity) {
    float sleep_threshold = 0.001f;

    if (sleep_threshold < velocity.Length()) {
        position += velocity * delta_time;
    } // if
    return position;
}

ratchet::component::TransformComponent::TransformComponent(int priority) :
    super(priority),
    _velocity_com() {
}

ratchet::component::TransformComponent::TransformComponent(const TransformComponent& obj) :
    super(obj),
    _velocity_com() {
}

ratchet::component::TransformComponent::~TransformComponent() {
}

std::string ratchet::component::TransformComponent::GetType(void) const {
    return "TransformComponent";
}

bool ratchet::component::TransformComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    return true;
}

bool ratchet::component::TransformComponent::Update(float delta_time) {
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

bool ratchet::component::TransformComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::TransformComponent::Clone(void) {
    return std::make_shared<ratchet::component::TransformComponent>(*this);
}