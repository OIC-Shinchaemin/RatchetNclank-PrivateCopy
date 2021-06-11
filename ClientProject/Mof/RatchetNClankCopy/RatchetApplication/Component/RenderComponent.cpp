#include "RenderComponent.h"


ratchet::RenderComponent::RenderComponent(int priority) :
    super(priority),
    _path() {
}

ratchet::RenderComponent::RenderComponent(const RenderComponent& obj) :
    super(obj),
    _path(obj._path){
}

ratchet::RenderComponent::~RenderComponent() {
}

void ratchet::RenderComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    _ASSERT_EXPR(param.HasMember("path"), L"�w�肳�ꂽ�^������܂���");
    _ASSERT_EXPR(param["path"].IsString(), L"�w�肳�ꂽ�^�ł���܂���");
    this->_path = param["path"].GetString();
}

std::string ratchet::RenderComponent::GetPath(void) const {
    return this->_path;
}

bool ratchet::RenderComponent::IsRender(void) const {
    return true;
}

bool ratchet::RenderComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool ratchet::RenderComponent::Render(void) {
    return false;
}

bool ratchet::RenderComponent::Release(void) {
    super::Release();
    return true;
}