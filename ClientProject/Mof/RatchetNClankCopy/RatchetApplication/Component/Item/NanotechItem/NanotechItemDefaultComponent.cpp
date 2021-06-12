#include "NanotechItemDefaultComponent.h"


ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::NanotechItemDefaultComponent(int priority) :
    super(priority) {
}

ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::NanotechItemDefaultComponent(const ratchet::component::item::nanotechitem::NanotechItemDefaultComponent& obj) :
    super(obj) {
}

ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::~NanotechItemDefaultComponent() {
}

std::string ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::GetType(void) const {
    return "NanotechItemDefaultComponent";
}

std::string_view ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kDefault;
}

bool ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::Update(float delta_time) {
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

bool ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::nanotechitem::NanotechItemDefaultComponent>(*this);
}

bool ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemDefaultComponent::End(void) {
    super::End();
    return true;
}