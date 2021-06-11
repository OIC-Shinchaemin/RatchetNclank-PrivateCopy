#include "InvincibleComponent.h"


rachet::InvincibleComponent::InvincibleComponent(int priority) :
    super(priority),
    _invincible() {
}

rachet::InvincibleComponent::InvincibleComponent(const InvincibleComponent& obj) :
    super(obj),
    _invincible() {
}

rachet::InvincibleComponent::~InvincibleComponent() {
}

std::string rachet::InvincibleComponent::GetType(void) const {
    return "InvincibleComponent";
}

bool rachet::InvincibleComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::InvincibleComponent::Update(float delta_time) {
    if (_invincible.Tick(delta_time)) {
        super::Inactivate();
    } // if
    return true;
}

bool rachet::InvincibleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::InvincibleComponent::Clone(void) {
    return std::make_shared<rachet::InvincibleComponent>(*this);
}

bool rachet::InvincibleComponent::Activate(void) {
    if (this->IsActive()) {
        return false;
    } // if

    super::Activate();
    _invincible.Initialize(1.0f, false);
    return true;
}