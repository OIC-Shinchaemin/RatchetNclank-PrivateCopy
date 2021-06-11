#include "Component.h"


std::weak_ptr<rachet::ResourceMgr> rachet::Component::_resource_manager;
std::weak_ptr<base::ui::UICanvas> rachet::Component::_ui_canvas;


void rachet::Component::SetResourceManager(const std::shared_ptr<rachet::ResourceMgr>& ptr) {
    _resource_manager = ptr;
}

void rachet::Component::SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr) {
    _ui_canvas = ptr;
}

rachet::Component::Component(int priority) :
    _owner(),
    _priority(priority),
    _active(false) {
}

rachet::Component::Component(const Component& obj) :
    _owner(),
    _priority(obj._priority),
    _active(obj._active) {
}

rachet::Component::~Component() {
}

void rachet::Component::SetOwner(const std::shared_ptr<rachet::Actor>& ptr) {
    this->_owner = ptr;
}

void rachet::Component::SetParam(const rapidjson::Value& param) {
    _ASSERT_EXPR(param.HasMember("priority"), L"パラメータに処理優先度がありません");
    _ASSERT_EXPR(param["priority"].IsInt(), L"パラメータの処理優先度がInt型でありません");

    this->_priority = param["priority"].GetInt();
}

std::shared_ptr<rachet::Actor> rachet::Component::GetOwner(void) const {
    if (auto owner = this->_owner.lock()) {
        return owner;
    } // if
    return nullptr;
}

int rachet::Component::GetPriority(void) const {
    return this->_priority;
}

bool rachet::Component::IsActive(void) const {
    return this->_active;
}

bool rachet::Component::IsInput(void) const {
    return false;
}

bool rachet::Component::IsUpdate(void) const {
    return false;
}

bool rachet::Component::IsRender(void) const {
#ifdef _DEBUG
    return true;
#endif // _DEBUG
    return false;
}

bool rachet::Component::Activate(void) {
    this->_active = true;
    return true;
}

bool rachet::Component::Inactivate(void) {
    this->_active = false;
    return true;
}

bool rachet::Component::Initialize(void) {
    _ASSERT_EXPR(!_owner.expired(), L"コンポーネントのアクターが登録されていません");
    return true;
}

bool rachet::Component::Input(void) {
    return false;
}

bool rachet::Component::Update(float delta_time) {
    return false;
}

bool rachet::Component::Render(void) {
    return false;
}

bool rachet::Component::Release(void) {
    _owner.reset();
    return true;
}
#ifdef _DEBUG
bool rachet::Component::DebugRender(void) {
    return false;
}
#endif // _DEBUG