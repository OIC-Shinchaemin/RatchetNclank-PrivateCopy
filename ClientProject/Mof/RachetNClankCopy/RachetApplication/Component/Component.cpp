#include "Component.h"


std::weak_ptr<my::ResourceMgr> my::Component::_resource_manager;
std::weak_ptr<base::ui::UICanvas> my::Component::_ui_canvas;


void my::Component::SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr) {
    _resource_manager = ptr;
}

void my::Component::SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr) {
    _ui_canvas = ptr;
}

my::Component::Component(int priority) :
    _owner(),
    _priority(priority),
    _active(false) {
}

my::Component::Component(const Component& obj) :
    _owner(),
    _priority(obj._priority),
    _active(obj._active) {
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
#ifdef _DEBUG
    return true;
#endif // _DEBUG
    return false;
}

bool my::Component::Activate(void) {
    this->_active = true;
    return true;
}

bool my::Component::Inactivate(void) {
    this->_active = false;
    return true;
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
#ifdef _DEBUG
bool my::Component::DebugRender(void) {
    return false;
}
#endif // _DEBUG