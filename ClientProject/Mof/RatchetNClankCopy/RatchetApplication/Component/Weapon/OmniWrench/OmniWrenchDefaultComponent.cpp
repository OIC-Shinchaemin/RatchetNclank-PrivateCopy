#include "OmniWrenchDefaultComponent.h"

#include "../../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"


void ratchet::component::weapon::OmniWrenchDefaultComponent::ChageState(const std::string& name) {
    if (auto state_com = _action_state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

ratchet::component::weapon::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(int priority) :
    super(priority),
    _velocity_com(),
    _action_state_com() {
}

ratchet::component::weapon::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(const OmniWrenchDefaultComponent& obj) :
    super(obj),
    _velocity_com(),
    _action_state_com() {
}

ratchet::component::weapon::OmniWrenchDefaultComponent::~OmniWrenchDefaultComponent() {
}

std::string ratchet::component::weapon::OmniWrenchDefaultComponent::GetType(void) const {
    return "OmniWrenchDefaultComponent";
}

std::string_view ratchet::component::weapon::OmniWrenchDefaultComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionDefaultState;
}

bool ratchet::component::weapon::OmniWrenchDefaultComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<ratchet::component::weapon::OmniWrenchActionStateComponent>();
    return true;
}

bool ratchet::component::weapon::OmniWrenchDefaultComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::weapon::OmniWrenchDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::weapon::OmniWrenchDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::component::weapon::OmniWrenchDefaultComponent>(*this);
}

bool ratchet::component::weapon::OmniWrenchDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::component::weapon::OmniWrenchDefaultComponent::End(void) {
    super::End();
    return true;
}