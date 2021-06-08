#include "BulletItemDefaultComponent.h"


my::BulletItemDefaultComponent::BulletItemDefaultComponent(int priority) :
    super(priority) {
}

my::BulletItemDefaultComponent::BulletItemDefaultComponent(const BulletItemDefaultComponent& obj) :
    super(obj) {
}

my::BulletItemDefaultComponent::~BulletItemDefaultComponent() {
}

std::string my::BulletItemDefaultComponent::GetType(void) const {
    return "BulletItemDefaultComponent";
}

std::string_view my::BulletItemDefaultComponent::GetStateType(void) const {
    return state::BulletItemActionType::kDefault;
}

bool my::BulletItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::BulletItemDefaultComponent::Update(float delta_time) {
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

bool my::BulletItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BulletItemDefaultComponent::Clone(void) {
    return std::make_shared<my::BulletItemDefaultComponent>(*this);
}

bool my::BulletItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool my::BulletItemDefaultComponent::End(void) {
    super::End();
    return true;
}