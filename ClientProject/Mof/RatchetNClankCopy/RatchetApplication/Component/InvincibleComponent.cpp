#include "InvincibleComponent.h"


ratchet::component::InvincibleComponent::InvincibleComponent(int priority) :
    super(priority),
    _invincible() {
}

ratchet::component::InvincibleComponent::InvincibleComponent(const InvincibleComponent& obj) :
    super(obj),
    _invincible() {
}

ratchet::component::InvincibleComponent::~InvincibleComponent() {
}

std::string ratchet::component::InvincibleComponent::GetType(void) const {
    return "InvincibleComponent";
}

bool ratchet::component::InvincibleComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::InvincibleComponent::Update(float delta_time) {
    if (_invincible.Tick(delta_time)) {
        super::Inactivate();
    } // if
    return true;
}

bool ratchet::component::InvincibleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::InvincibleComponent::Clone(void) {
    return std::make_shared<ratchet::component::InvincibleComponent>(*this);
}

bool ratchet::component::InvincibleComponent::Activate(void) {
    if (this->IsActive()) {
        return false;
    } // if

    super::Activate();
    _invincible.Initialize(1.0f, false);
    return true;
}