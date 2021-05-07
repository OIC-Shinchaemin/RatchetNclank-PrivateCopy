#include "RenderComponent.h"


my::RenderComponent::RenderComponent(int priority) :
    super(priority),
    _path() {
}

my::RenderComponent::~RenderComponent() {
}

void my::RenderComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    _ASSERT_EXPR(param.HasMember("path"), L"�w�肳�ꂽ�^������܂���");
    _ASSERT_EXPR(param["path"].IsString(), L"�w�肳�ꂽ�^�ł���܂���");
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
    super::_active = true;
    return true;
}

bool my::RenderComponent::Render(void) {
    return false;
}

bool my::RenderComponent::Render(const Mof::CMatrix44& world) {
    return false;
}

bool my::RenderComponent::Release(void) {
    super::Release();
    return true;
}

bool my::RenderComponent::DebugRender(void) {
    return false;
}