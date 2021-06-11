#include "BulletItemDefaultComponent.h"


rachet::BulletItemDefaultComponent::BulletItemDefaultComponent(int priority) :
    super(priority) {
}

rachet::BulletItemDefaultComponent::BulletItemDefaultComponent(const BulletItemDefaultComponent& obj) :
    super(obj) {
}

rachet::BulletItemDefaultComponent::~BulletItemDefaultComponent() {
}

std::string rachet::BulletItemDefaultComponent::GetType(void) const {
    return "BulletItemDefaultComponent";
}

std::string_view rachet::BulletItemDefaultComponent::GetStateType(void) const {
    return state::BulletItemActionType::kDefault;
}

bool rachet::BulletItemDefaultComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::BulletItemDefaultComponent::Update(float delta_time) {
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

bool rachet::BulletItemDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BulletItemDefaultComponent::Clone(void) {
    return std::make_shared<rachet::BulletItemDefaultComponent>(*this);
}

bool rachet::BulletItemDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool rachet::BulletItemDefaultComponent::End(void) {
    super::End();
    return true;
}