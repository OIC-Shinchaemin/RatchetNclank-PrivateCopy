#include "UpdateComponent.h"


rachet::UpdateComponent::UpdateComponent(int priority) :
    super(priority) {
}

rachet::UpdateComponent::UpdateComponent(const UpdateComponent& obj) :
    super(obj) {
}

rachet::UpdateComponent::~UpdateComponent() {
}

void rachet::UpdateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

bool rachet::UpdateComponent::IsUpdate(void) const {
    return true;
}

bool rachet::UpdateComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::UpdateComponent::Update(float delta_time) {
    return true;
}

bool rachet::UpdateComponent::Release(void) {
    super::Release();
    return true;
}