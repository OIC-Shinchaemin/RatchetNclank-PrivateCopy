#include "OmniWrenchDefaultComponent.h"

#include "../../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"


void ratchet::OmniWrenchDefaultComponent::ChageState(const std::string& name) {
    if (auto state_com = _action_state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

ratchet::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(int priority) :
    super(priority),
    _velocity_com(),
    _action_state_com() {
}

ratchet::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(const OmniWrenchDefaultComponent& obj) :
    super(obj),
    _velocity_com(),
    _action_state_com() {
}

ratchet::OmniWrenchDefaultComponent::~OmniWrenchDefaultComponent() {
}

std::string ratchet::OmniWrenchDefaultComponent::GetType(void) const {
    return "OmniWrenchDefaultComponent";
}

std::string_view ratchet::OmniWrenchDefaultComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionDefaultState;
}

bool ratchet::OmniWrenchDefaultComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<ratchet::OmniWrenchActionStateComponent>();
    return true;
}

bool ratchet::OmniWrenchDefaultComponent::Update(float delta_time) {
    return true;
}

bool ratchet::OmniWrenchDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::OmniWrenchDefaultComponent::Clone(void) {
    return std::make_shared<ratchet::OmniWrenchDefaultComponent>(*this);
}

bool ratchet::OmniWrenchDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool ratchet::OmniWrenchDefaultComponent::End(void) {
    super::End();
    return true;
}