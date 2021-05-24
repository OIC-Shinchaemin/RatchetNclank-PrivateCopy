#include "OmniWrenchDefaultComponent.h"

#include "../../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"


void my::OmniWrenchDefaultComponent::ChageState(const std::string& name) {
    if (auto state_com = _action_state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(int priority) :
    super(priority),
    _velocity_com(),
    _action_state_com() {
}

my::OmniWrenchDefaultComponent::OmniWrenchDefaultComponent(const OmniWrenchDefaultComponent& obj) :
    super(obj),
    _velocity_com(),
    _action_state_com() {
}

my::OmniWrenchDefaultComponent::~OmniWrenchDefaultComponent() {
}

std::string my::OmniWrenchDefaultComponent::GetType(void) const {
    return "OmniWrenchDefaultComponent";
}

std::string_view my::OmniWrenchDefaultComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionDefaultState;
}

bool my::OmniWrenchDefaultComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<my::OmniWrenchActionStateComponent>();
    return true;
}

bool my::OmniWrenchDefaultComponent::Update(float delta_time) {
    return true;
}

bool my::OmniWrenchDefaultComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::OmniWrenchDefaultComponent::Clone(void) {
    return std::make_shared<my::OmniWrenchDefaultComponent>(*this);
}

bool my::OmniWrenchDefaultComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool my::OmniWrenchDefaultComponent::End(void) {
    super::End();
    return true;
}