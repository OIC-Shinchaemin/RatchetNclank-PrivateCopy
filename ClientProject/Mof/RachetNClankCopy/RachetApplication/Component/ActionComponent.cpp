#include "ActionComponent.h"


void my::ActionComponent::ChageState(const std::string& name) {
}

my::ActionComponent::ActionComponent(int priority) :
    super(priority) {
}

my::ActionComponent::ActionComponent(const ActionComponent& obj) :
    super(obj._priority) {
}

my::ActionComponent::~ActionComponent() {
}

std::string my::ActionComponent::GetType(void) const {
    return "ActionComponent";
}

bool my::ActionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::ActionComponent::Update(float delta_time) {
    return true;
}

bool my::ActionComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::ActionComponent::Clone(void) {
    return std::make_shared<my::ActionComponent>(*this);
}

bool my::ActionComponent::Start(void) {
    return true;
}