#include "Component.h"


std::weak_ptr<ratchet::ResourceMgr> ratchet::component::Component::Component::_resource_manager;
std::weak_ptr<base::ui::UICanvas> ratchet::component::Component::Component::_ui_canvas;


void ratchet::component::Component::Component::SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
    _resource_manager = ptr;
}

void ratchet::component::Component::Component::SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr) {
    _ui_canvas = ptr;
}

ratchet::component::Component::Component::Component(int priority) :
    _owner(),
    _priority(priority),
    _active(false) {
}

ratchet::component::Component::Component::Component(const Component& obj) :
    _owner(),
    _priority(obj._priority),
    _active(obj._active) {
}

ratchet::component::Component::Component::~Component() {
}

void ratchet::component::Component::Component::SetOwner(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_owner = ptr;
}

void ratchet::component::Component::Component::SetParam(const rapidjson::Value& param) {
    _ASSERT_EXPR(param.HasMember("priority"), L"パラメータに処理優先度がありません");
    _ASSERT_EXPR(param["priority"].IsInt(), L"パラメータの処理優先度がInt型でありません");

    this->_priority = param["priority"].GetInt();
}

std::shared_ptr<ratchet::actor::Actor> ratchet::component::Component::Component::GetOwner(void) const {
    if (auto owner = this->_owner.lock()) {
        return owner;
    } // if
    return nullptr;
}

int ratchet::component::Component::Component::GetPriority(void) const {
    return this->_priority;
}

bool ratchet::component::Component::Component::IsActive(void) const {
    return this->_active;
}

bool ratchet::component::Component::Component::IsInput(void) const {
    return false;
}

bool ratchet::component::Component::Component::IsUpdate(void) const {
    return false;
}

bool ratchet::component::Component::Component::IsRender(void) const {
#ifdef _DEBUG
    return true;
#endif // _DEBUG
    return false;
}

bool ratchet::component::Component::Component::Activate(void) {
    this->_active = true;
    return true;
}

bool ratchet::component::Component::Component::Inactivate(void) {
    this->_active = false;
    return true;
}

bool ratchet::component::Component::Component::Initialize(void) {
    _ASSERT_EXPR(!_owner.expired(), L"コンポーネントのアクターが登録されていません");
    return true;
}

bool ratchet::component::Component::Component::Input(void) {
    return false;
}

bool ratchet::component::Component::Component::Update(float delta_time) {
    return false;
}

bool ratchet::component::Component::Component::Render(void) {
    return false;
}

bool ratchet::component::Component::Component::Release(void) {
    _owner.reset();
    return true;
}
#ifdef _DEBUG
bool ratchet::component::Component::Component::DebugRender(void) {
    return false;
}
#endif // _DEBUG