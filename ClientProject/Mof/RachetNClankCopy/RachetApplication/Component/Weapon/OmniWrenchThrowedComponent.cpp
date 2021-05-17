#include "OmniWrenchThrowedComponent.h"

#include "../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"
#include "../../State/OmniWrenchActionStateDefine.h"


void my::OmniWrenchThrowedComponent::ChageState(const std::string& name) {
    if (auto state_com = _action_state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(int priority) :
    super(priority),
    _velocity_com(),
    _action_state_com() {
}

my::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(const OmniWrenchThrowedComponent& obj) :
    super(obj),
    _velocity_com(),
    _action_state_com() {
}

my::OmniWrenchThrowedComponent::~OmniWrenchThrowedComponent() {
}

std::string my::OmniWrenchThrowedComponent::GetType(void) const {
    return "OmniWrenchThrowedComponent";
}

std::string_view my::OmniWrenchThrowedComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionThrowedState;
}

bool my::OmniWrenchThrowedComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<my::OmniWrenchActionStateComponent>();
    return true;
}

bool my::OmniWrenchThrowedComponent::Update(float delta_time) {
    return true;
}

bool my::OmniWrenchThrowedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::OmniWrenchThrowedComponent::Clone(void) {
    return std::make_shared<my::OmniWrenchThrowedComponent>(*this);
}

bool my::OmniWrenchThrowedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    return true;
}

bool my::OmniWrenchThrowedComponent::End(void) {
    super::End();
    return true;
}