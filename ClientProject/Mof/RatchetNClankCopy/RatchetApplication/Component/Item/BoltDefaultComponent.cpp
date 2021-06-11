#include "BoltDefaultComponent.h"


ratchet::BoltDefaultComponent::BoltDefaultComponent(int priority) :
    super(priority) {
}

ratchet::BoltDefaultComponent::BoltDefaultComponent(const BoltDefaultComponent& obj) :
    super(obj) {
}

ratchet::BoltDefaultComponent::~BoltDefaultComponent() {
}

std::string ratchet::BoltDefaultComponent::GetType(void) const {
    return "BoltDefaultComponent";
}

std::string_view ratchet::BoltDefaultComponent::GetStateType(void) const {
    return state::BoltActionType::kDefault;
}

bool ratchet::BoltDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::BoltDefaultComponent::Update(float delta_time) {
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

bool ratchet::BoltDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::BoltDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::BoltDefaultComponent>(*this);
}

bool ratchet::BoltDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::BoltDefaultComponent::End(void) {
    super::End();
    return true;
}