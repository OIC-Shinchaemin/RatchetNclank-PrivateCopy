#include "InvincibleComponent.h"


ratchet::InvincibleComponent::InvincibleComponent(int priority) :
    super(priority),
    _invincible() {
}

ratchet::InvincibleComponent::InvincibleComponent(const InvincibleComponent& obj) :
    super(obj),
    _invincible() {
}

ratchet::InvincibleComponent::~InvincibleComponent() {
}

std::string ratchet::InvincibleComponent::GetType(void) const {
    return "InvincibleComponent";
}

bool ratchet::InvincibleComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::InvincibleComponent::Update(float delta_time) {
    if (_invincible.Tick(delta_time)) {
        super::Inactivate();
    } // if
    return true;
}

bool ratchet::InvincibleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::InvincibleComponent::Clone(void) {
    return std::make_shared<ratchet::InvincibleComponent>(*this);
}

bool ratchet::InvincibleComponent::Activate(void) {
    if (this->IsActive()) {
        return false;
    } // if

    super::Activate();
    _invincible.Initialize(1.0f, false);
    return true;
}