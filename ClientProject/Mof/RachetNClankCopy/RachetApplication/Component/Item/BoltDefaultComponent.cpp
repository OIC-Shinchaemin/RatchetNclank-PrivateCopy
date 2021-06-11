#include "BoltDefaultComponent.h"


rachet::BoltDefaultComponent::BoltDefaultComponent(int priority) :
    super(priority) {
}

rachet::BoltDefaultComponent::BoltDefaultComponent(const BoltDefaultComponent& obj) :
    super(obj) {
}

rachet::BoltDefaultComponent::~BoltDefaultComponent() {
}

std::string rachet::BoltDefaultComponent::GetType(void) const {
    return "BoltDefaultComponent";
}

std::string_view rachet::BoltDefaultComponent::GetStateType(void) const {
    return state::BoltActionType::kDefault;
}

bool rachet::BoltDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::BoltDefaultComponent::Update(float delta_time) {
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

bool rachet::BoltDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BoltDefaultComponent::Clone(void) {
    return std::make_shared<rachet::BoltDefaultComponent>(*this);
}

bool rachet::BoltDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool rachet::BoltDefaultComponent::End(void) {
    super::End();
    return true;
}