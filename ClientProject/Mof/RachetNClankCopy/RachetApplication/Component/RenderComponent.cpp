#include "RenderComponent.h"


my::RenderComponent::RenderComponent(int priority) :
    super(priority),
    _path() {
}

my::RenderComponent::RenderComponent(const RenderComponent& obj) :
    super(obj),
    _path(obj._path){
}

my::RenderComponent::~RenderComponent() {
}

void my::RenderComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    _ASSERT_EXPR(param.HasMember("path"), L"Žw’è‚³‚ê‚½Œ^‚ª‚ ‚è‚Ü‚¹‚ñ");
    _ASSERT_EXPR(param["path"].IsString(), L"Žw’è‚³‚ê‚½Œ^‚Å‚ ‚è‚Ü‚¹‚ñ");
    this->_path = param["path"].GetString();
}

std::string my::RenderComponent::GetPath(void) const {
    return this->_path;
}

bool my::RenderComponent::IsRender(void) const {
    return true;
}

bool my::RenderComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool my::RenderComponent::Render(void) {
    return false;
}

bool my::RenderComponent::Release(void) {
    super::Release();
    return true;
}