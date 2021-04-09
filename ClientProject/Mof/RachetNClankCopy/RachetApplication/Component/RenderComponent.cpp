#include "RenderComponent.h"


my::RenderComponent::RenderComponent(int priority) :
    super(priority) {
}

my::RenderComponent::~RenderComponent() {
}

void my::RenderComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

bool my::RenderComponent::IsRender(void) const {
    return true;
}

bool my::RenderComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::RenderComponent::Render(void) {
    return false;
}

bool my::RenderComponent::Release(void) {
    super::Release();
    return true;
}

bool my::RenderComponent::DebugRender(void) {
    return false;
}