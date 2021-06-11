#include "OmniWrenchDefaultComponent.h"

#include "../../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"


void rachet::OmniWrenchDefaultComponent::ChageState(const std::string& name) {
    if (auto state_com = _action_state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

rachet::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(int priority) :
    super(priority),
    _velocity_com(),
    _action_state_com() {
}

rachet::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(const OmniWrenchDefaultComponent& obj) :
    super(obj),
    _velocity_com(),
    _action_state_com() {
}

rachet::OmniWrenchDefaultComponent::~OmniWrenchDefaultComponent() {
}

std::string rachet::OmniWrenchDefaultComponent::GetType(void) const {
    return "OmniWrenchDefaultComponent";
}

std::string_view rachet::OmniWrenchDefaultComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionDefaultState;
}

bool rachet::OmniWrenchDefaultComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<rachet::OmniWrenchActionStateComponent>();
    return true;
}

bool rachet::OmniWrenchDefaultComponent::Update(float delta_time) {
    return true;
}

bool rachet::OmniWrenchDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::OmniWrenchDefaultComponent::Clone(void) {
    return std::make_shared<rachet::OmniWrenchDefaultComponent>(*this);
}

bool rachet::OmniWrenchDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool rachet::OmniWrenchDefaultComponent::End(void) {
    super::End();
    return true;
}