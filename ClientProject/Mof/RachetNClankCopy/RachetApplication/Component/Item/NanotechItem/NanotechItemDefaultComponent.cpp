#include "NanotechItemDefaultComponent.h"


my::NanotechItemDefaultComponent::NanotechItemDefaultComponent(int priority) :
    super(priority) {
}

my::NanotechItemDefaultComponent::NanotechItemDefaultComponent(const my::NanotechItemDefaultComponent& obj) :
    super(obj) {
}

my::NanotechItemDefaultComponent::~NanotechItemDefaultComponent() {
}

std::string my::NanotechItemDefaultComponent::GetType(void) const {
    return "NanotechItemDefaultComponent";
}

std::string_view my::NanotechItemDefaultComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kDefault;
}

bool my::NanotechItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::NanotechItemDefaultComponent::Update(float delta_time) {
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

bool my::NanotechItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::NanotechItemDefaultComponent::Clone(void) {
    return std::make_shared<my::NanotechItemDefaultComponent>(*this);
}

bool my::NanotechItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool my::NanotechItemDefaultComponent::End(void) {
    super::End();
    return true;
}