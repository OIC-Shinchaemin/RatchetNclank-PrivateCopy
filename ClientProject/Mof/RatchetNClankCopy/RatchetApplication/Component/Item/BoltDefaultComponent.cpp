#include "BoltDefaultComponent.h"


ratchet::component::item::BoltDefaultComponent::BoltDefaultComponent(int priority) :
    super(priority) {
}

ratchet::component::item::BoltDefaultComponent::BoltDefaultComponent(const BoltDefaultComponent& obj) :
    super(obj) {
}

ratchet::component::item::BoltDefaultComponent::~BoltDefaultComponent() {
}

std::string ratchet::component::item::BoltDefaultComponent::GetType(void) const {
    return "BoltDefaultComponent";
}

std::string_view ratchet::component::item::BoltDefaultComponent::GetStateType(void) const {
    return state::BoltActionType::kDefault;
}

bool ratchet::component::item::BoltDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::item::BoltDefaultComponent::Update(float delta_time) {
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

bool ratchet::component::item::BoltDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::BoltDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::BoltDefaultComponent>(*this);
}

bool ratchet::component::item::BoltDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::component::item::BoltDefaultComponent::End(void) {
    super::End();
    return true;
}