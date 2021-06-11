#include "BulletItemDefaultComponent.h"


ratchet::BulletItemDefaultComponent::BulletItemDefaultComponent(int priority) :
    super(priority) {
}

ratchet::BulletItemDefaultComponent::BulletItemDefaultComponent(const BulletItemDefaultComponent& obj) :
    super(obj) {
}

ratchet::BulletItemDefaultComponent::~BulletItemDefaultComponent() {
}

std::string ratchet::BulletItemDefaultComponent::GetType(void) const {
    return "BulletItemDefaultComponent";
}

std::string_view ratchet::BulletItemDefaultComponent::GetStateType(void) const {
    return state::BulletItemActionType::kDefault;
}

bool ratchet::BulletItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::BulletItemDefaultComponent::Update(float delta_time) {
    auto rotate = super::GetOwner()->GetRotate();
    if (rotate.x > math::kHalfPi) {
        rotate.x = math::kHalfPi;
        super::GetOwner()->SetRotate(rotate);
    } // if
    if (rotate.z > math::kHalfPi) {
        rotate.z = math::kHalfPi;
        super::GetOwner()->SetRotate(rotate);
    } // if

    return true;
}

bool ratchet::BulletItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BulletItemDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::BulletItemDefaultComponent>(*this);
}

bool ratchet::BulletItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::BulletItemDefaultComponent::End(void) {
    super::End();
    return true;
}