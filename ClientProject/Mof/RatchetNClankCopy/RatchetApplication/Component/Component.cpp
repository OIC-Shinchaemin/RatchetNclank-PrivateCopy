#include "Component.h"


std::weak_ptr<ratchet::ResourceMgr> ratchet::Component::_resource_manager;
std::weak_ptr<base::ui::UICanvas> ratchet::Component::_ui_canvas;


void ratchet::Component::SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
    _resource_manager = ptr;
}

void ratchet::Component::SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr) {
    _ui_canvas = ptr;
}

ratchet::Component::Component(int priority) :
    _owner(),
    _priority(priority),
    _active(false) {
}

ratchet::Component::Component(const Component& obj) :
    _owner(),
    _priority(obj._priority),
    _active(obj._active) {
}

ratchet::Component::~Component() {
}

void ratchet::Component::SetOwner(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_owner = ptr;
}

void ratchet::Component::SetParam(const rapidjson::Value& param) {
    _ASSERT_EXPR(param.HasMember("priority"), L"パラメータに処理優先度がありません");
    _ASSERT_EXPR(param["priority"].IsInt(), L"パラメータの処理優先度がInt型でありません");

    this->_priority = param["priority"].GetInt();
}

std::shared_ptr<ratchet::actor::Actor> ratchet::Component::GetOwner(void) const {
    if (auto owner = this->_owner.lock()) {
        return owner;
    } // if
    return nullptr;
}

int ratchet::Component::GetPriority(void) const {
    return this->_priority;
}

bool ratchet::Component::IsActive(void) const {
    return this->_active;
}

bool ratchet::Component::IsInput(void) const {
    return false;
}

bool ratchet::Component::IsUpdate(void) const {
    return false;
}

bool ratchet::Component::IsRender(void) const {
#ifdef _DEBUG
    return true;
#endif // _DEBUG
    return false;
}

bool ratchet::Component::Activate(void) {
    this->_active = true;
    return true;
}

bool ratchet::Component::Inactivate(void) {
    this->_active = false;
    return true;
}

bool ratchet::Component::Initialize(void) {
    _ASSERT_EXPR(!_owner.expired(), L"コンポーネントのアクターが登録されていません");
    return true;
}

bool ratchet::Component::Input(void) {
    return false;
}

bool ratchet::Component::Update(float delta_time) {
    return false;
}

bool ratchet::Component::Render(void) {
    return false;
}

bool ratchet::Component::Release(void) {
    _owner.reset();
    return true;
}
#ifdef _DEBUG
bool ratchet::Component::DebugRender(void) {
    return false;
}
#endif // _DEBUG