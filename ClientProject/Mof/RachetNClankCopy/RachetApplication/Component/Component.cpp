#include "Component.h"


std::weak_ptr<my::ResourceMgr> my::Component::_resource_manager;
std::weak_ptr<my::UICanvas> my::Component::_ui_canvas;

void my::Component::SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr) {
    _resource_manager = ptr;
}

void my::Component::SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr) {
    _ui_canvas = ptr;
}

my::Component::Component(int priority) :
    _owner(),
    _priority(priority),
    _active(false) {
}

my::Component::~Component() {
}

void my::Component::SetOwner(const std::shared_ptr<my::Actor>& ptr) {
    this->_owner = ptr;
}

void my::Component::SetParam(const rapidjson::Value& param) {
    _ASSERT_EXPR(param.HasMember("priority"), L"パラメータに処理優先度がありません");
    _ASSERT_EXPR(param["priority"].IsInt(), L"パラメータの処理優先度がInt型でありません");

    this->_priority = param["priority"].GetInt();
}

std::shared_ptr<my::Actor> my::Component::GetOwner(void) const {
    if (auto owner = this->_owner.lock()) {
        return owner;
    } // if
    return nullptr;
}

int my::Component::GetPriority(void) const {
    return this->_priority;
}

bool my::Component::IsActive(void) const {
    return this->_active;
}

bool my::Component::IsInput(void) const {
    return false;
}

bool my::Component::IsUpdate(void) const {
    return false;
}

bool my::Component::IsRender(void) const {
    return false;
}

bool my::Component::Initialize(void) {
    _ASSERT_EXPR(!_owner.expired(), L"コンポーネントのアクターが登録されていません");
    return true;
}

bool my::Component::Input(void) {
    return false;
}

bool my::Component::Update(float delta_time) {
    return false;
}

bool my::Component::Render(void) {
    return false;
}

bool my::Component::Release(void) {
    _owner.reset();
    return true;
}