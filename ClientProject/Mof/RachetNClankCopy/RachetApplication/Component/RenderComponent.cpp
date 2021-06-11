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
    _ASSERT_EXPR(param.HasMember("path"), L"�w�肳�ꂽ�^������܂���");
    _ASSERT_EXPR(param["path"].IsString(), L"�w�肳�ꂽ�^�ł���܂���");
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