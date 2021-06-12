#include "BulletItemDefaultComponent.h"


ratchet::component::item::bulletitem::BulletItemDefaultComponent::BulletItemDefaultComponent(int priority) :
    super(priority) {
}

ratchet::component::item::bulletitem::BulletItemDefaultComponent::BulletItemDefaultComponent(const BulletItemDefaultComponent& obj) :
    super(obj) {
}

ratchet::component::item::bulletitem::BulletItemDefaultComponent::~BulletItemDefaultComponent() {
}

std::string ratchet::component::item::bulletitem::BulletItemDefaultComponent::GetType(void) const {
    return "BulletItemDefaultComponent";
}

std::string_view ratchet::component::item::bulletitem::BulletItemDefaultComponent::GetStateType(void) const {
    return state::BulletItemActionType::kDefault;
}

bool ratchet::component::item::bulletitem::BulletItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::item::bulletitem::BulletItemDefaultComponent::Update(float delta_time) {
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

bool ratchet::component::item::bulletitem::BulletItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::bulletitem::BulletItemDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::bulletitem::BulletItemDefaultComponent>(*this);
}

bool ratchet::component::item::bulletitem::BulletItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::component::item::bulletitem::BulletItemDefaultComponent::End(void) {
    super::End();
    return true;
}