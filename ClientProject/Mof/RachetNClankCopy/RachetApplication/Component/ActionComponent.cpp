#include "ActionComponent.h"


my::ActionComponent::ActionComponent(int priority) :
    super(priority) {
}

my::ActionComponent::ActionComponent(const ActionComponent& obj) :
    super(obj) {
}

my::ActionComponent::~ActionComponent() {
}

std::string my::ActionComponent::GetType(void) const {
    return "ActionComponent";
}

std::string_view my::ActionComponent::GetStateType(void) const {
    return std::string_view();
}

bool my::ActionComponent::Start(void) {
    super::Activate();
    return true;
}

bool my::ActionComponent::End(void) {
    super::Inactivate();
    return true;
}