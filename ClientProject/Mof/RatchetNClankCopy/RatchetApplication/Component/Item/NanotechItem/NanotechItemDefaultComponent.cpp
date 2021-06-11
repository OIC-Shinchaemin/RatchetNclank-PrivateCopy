#include "NanotechItemDefaultComponent.h"


ratchet::NanotechItemDefaultComponent::NanotechItemDefaultComponent(int priority) :
    super(priority) {
}

ratchet::NanotechItemDefaultComponent::NanotechItemDefaultComponent(const ratchet::NanotechItemDefaultComponent& obj) :
    super(obj) {
}

ratchet::NanotechItemDefaultComponent::~NanotechItemDefaultComponent() {
}

std::string ratchet::NanotechItemDefaultComponent::GetType(void) const {
    return "NanotechItemDefaultComponent";
}

std::string_view ratchet::NanotechItemDefaultComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kDefault;
}

bool ratchet::NanotechItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::NanotechItemDefaultComponent::Update(float delta_time) {
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

bool ratchet::NanotechItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::NanotechItemDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::NanotechItemDefaultComponent>(*this);
}

bool ratchet::NanotechItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::NanotechItemDefaultComponent::End(void) {
    super::End();
    return true;
}