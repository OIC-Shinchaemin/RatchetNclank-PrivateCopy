#include "RenderComponent.h"


ratchet::component::RenderComponent::RenderComponent(int priority) :
    super(priority),
    _path() {
}

ratchet::component::RenderComponent::RenderComponent(const RenderComponent& obj) :
    super(obj),
    _path(obj._path){
}

ratchet::component::RenderComponent::~RenderComponent() {
}

void ratchet::component::RenderComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    _ASSERT_EXPR(param.HasMember("path"), L"Žw’è‚³‚ê‚½Œ^‚ª‚ ‚è‚Ü‚¹‚ñ");
    _ASSERT_EXPR(param["path"].IsString(), L"Žw’è‚³‚ê‚½Œ^‚Å‚ ‚è‚Ü‚¹‚ñ");
    this->_path = param["path"].GetString();
}

std::string ratchet::component::RenderComponent::GetPath(void) const {
    return this->_path;
}

bool ratchet::component::RenderComponent::IsRender(void) const {
    return true;
}

bool ratchet::component::RenderComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool ratchet::component::RenderComponent::Render(void) {
    return false;
}

bool ratchet::component::RenderComponent::Release(void) {
    super::Release();
    return true;
}