#include "BoltDefaultComponent.h"


my::BoltDefaultComponent::BoltDefaultComponent(int priority) :
    super(priority) {
}

my::BoltDefaultComponent::BoltDefaultComponent(const BoltDefaultComponent& obj) :
    super(obj) {
}

my::BoltDefaultComponent::~BoltDefaultComponent() {
}

std::string my::BoltDefaultComponent::GetType(void) const {
    return "BoltDefaultComponent";
}

std::string_view my::BoltDefaultComponent::GetStateType(void) const {
    return state::BoltActionType::kDefault;
}

bool my::BoltDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::BoltDefaultComponent::Update(float delta_time) {
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

bool my::BoltDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BoltDefaultComponent::Clone(void) {
    return std::make_shared<my::BoltDefaultComponent>(*this);
}

bool my::BoltDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool my::BoltDefaultComponent::End(void) {
    super::End();
    return true;
}