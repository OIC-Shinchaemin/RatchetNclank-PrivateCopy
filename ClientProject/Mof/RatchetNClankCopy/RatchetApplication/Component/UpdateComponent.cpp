#include "UpdateComponent.h"


ratchet::UpdateComponent::UpdateComponent(int priority) :
    super(priority) {
}

ratchet::UpdateComponent::UpdateComponent(const UpdateComponent& obj) :
    super(obj) {
}

ratchet::UpdateComponent::~UpdateComponent() {
}

void ratchet::UpdateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

bool ratchet::UpdateComponent::IsUpdate(void) const {
    return true;
}

bool ratchet::UpdateComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::UpdateComponent::Update(float delta_time) {
    return true;
}

bool ratchet::UpdateComponent::Release(void) {
    super::Release();
    return true;
}