#include "NanotechItemDefaultComponent.h"


rachet::NanotechItemDefaultComponent::NanotechItemDefaultComponent(int priority) :
    super(priority) {
}

rachet::NanotechItemDefaultComponent::NanotechItemDefaultComponent(const rachet::NanotechItemDefaultComponent& obj) :
    super(obj) {
}

rachet::NanotechItemDefaultComponent::~NanotechItemDefaultComponent() {
}

std::string rachet::NanotechItemDefaultComponent::GetType(void) const {
    return "NanotechItemDefaultComponent";
}

std::string_view rachet::NanotechItemDefaultComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kDefault;
}

bool rachet::NanotechItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::NanotechItemDefaultComponent::Update(float delta_time) {
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

bool rachet::NanotechItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::NanotechItemDefaultComponent::Clone(void) {
    return std::make_shared<rachet::NanotechItemDefaultComponent>(*this);
}

bool rachet::NanotechItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool rachet::NanotechItemDefaultComponent::End(void) {
    super::End();
    return true;
}