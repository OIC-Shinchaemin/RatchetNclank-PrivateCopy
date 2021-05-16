#include "UpdateComponent.h"


my::UpdateComponent::UpdateComponent(int priority) :
    super(priority) {
}

my::UpdateComponent::UpdateComponent(const UpdateComponent& obj) :
    super(obj) {
}

my::UpdateComponent::~UpdateComponent() {
}

void my::UpdateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

bool my::UpdateComponent::IsUpdate(void) const {
    return true;
}

bool my::UpdateComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::UpdateComponent::Update(float delta_time) {
    return true;
}

bool my::UpdateComponent::Release(void) {
    super::Release();
    return true;
}