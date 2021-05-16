#include "InvincibleComponent.h"


my::InvincibleComponent::InvincibleComponent(int priority) :
    super(priority),
    _invincible() {
}

my::InvincibleComponent::InvincibleComponent(const InvincibleComponent& obj) :
    super(obj),
    _invincible() {
}

my::InvincibleComponent::~InvincibleComponent() {
}

std::string my::InvincibleComponent::GetType(void) const {
    return "InvincibleComponent";
}

bool my::InvincibleComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::InvincibleComponent::Update(float delta_time) {
    if (_invincible.Tick(delta_time)) {
        super::Inactivate();
    } // if
    return true;
}

bool my::InvincibleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::InvincibleComponent::Clone(void) {
    return std::make_shared<my::InvincibleComponent>(*this);
}

bool my::InvincibleComponent::Activate(void) {
    if (this->IsActive()) {
        return false;
    } // if

    super::Activate();
    _invincible.Initialize(1.0f, false);
    return true;
}