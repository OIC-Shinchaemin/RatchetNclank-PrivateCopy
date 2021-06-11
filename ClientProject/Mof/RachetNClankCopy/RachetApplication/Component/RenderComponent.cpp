#include "RenderComponent.h"


rachet::RenderComponent::RenderComponent(int priority) :
    super(priority),
    _path() {
}

rachet::RenderComponent::RenderComponent(const RenderComponent& obj) :
    super(obj),
    _path(obj._path){
}

rachet::RenderComponent::~RenderComponent() {
}

void rachet::RenderComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    _ASSERT_EXPR(param.HasMember("path"), L"Žw’è‚³‚ê‚½Œ^‚ª‚ ‚è‚Ü‚¹‚ñ");
    _ASSERT_EXPR(param["path"].IsString(), L"Žw’è‚³‚ê‚½Œ^‚Å‚ ‚è‚Ü‚¹‚ñ");
    this->_path = param["path"].GetString();
}

std::string rachet::RenderComponent::GetPath(void) const {
    return this->_path;
}

bool rachet::RenderComponent::IsRender(void) const {
    return true;
}

bool rachet::RenderComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool rachet::RenderComponent::Render(void) {
    return false;
}

bool rachet::RenderComponent::Release(void) {
    super::Release();
    return true;
}