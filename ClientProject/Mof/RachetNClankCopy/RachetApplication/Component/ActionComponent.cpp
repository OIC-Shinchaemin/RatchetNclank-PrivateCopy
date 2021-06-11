#include "ActionComponent.h"

#include "../Factory/FactoryManager.h"


ratchet::ActionComponent::ActionComponent(int priority) :
    super(priority),
    _current_action(),
    _children() {
}

ratchet::ActionComponent::ActionComponent(const ActionComponent& obj) :
    super(obj),
    _current_action(),
    _children() {
    this->_children.reserve(obj._children.size());
    for (auto& child : obj._children) {
        auto com = std::dynamic_pointer_cast<ratchet::ActionComponent>(child.second->Clone());
        this->_children.emplace(com->GetType().c_str(), com);
    } // for
}

ratchet::ActionComponent::~ActionComponent() {
}

void ratchet::ActionComponent::SetOwner(const std::shared_ptr<ratchet::Actor>& ptr) {
    super::SetOwner(ptr);
    for (auto& com : _children) {
        com.second->SetOwner(ptr);
    } // for
}

void ratchet::ActionComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* children = "children";
    
    if (param.HasMember(children)) {
        _ASSERT_EXPR(param[children].IsArray(), L"パラメータの指定された型でありません");
        _children.reserve(param[children].Size());
        for (int i = 0, n = param[children].Size(); i < n; i++) {
            auto& child = param[children][i];
            _ASSERT_EXPR(child.HasMember("type"), L"タイプがありません");
            _ASSERT_EXPR(child["type"].IsString(), L"タイプが指定された型でありません");
            _ASSERT_EXPR(child.HasMember("paramater"), L"パラメータがありません");
            _ASSERT_EXPR(child["paramater"].IsObject(), L"パラメータが指定された型でありません");

            auto& child_param = child["paramater"];
            std::string type = child["type"].GetString();

            auto com = ratchet::FactoryManager::Singleton().CreateComponent(type.c_str(), child_param);
            _children.emplace(com->GetType(), std::dynamic_pointer_cast<ratchet::ActionComponent>(com));
        } // for
    } // if
}

std::string ratchet::ActionComponent::GetType(void) const {
    return "ActionComponent";
}

std::string_view ratchet::ActionComponent::GetStateType(void) const {
    return std::string_view();
}

const std::unordered_map<std::string, std::shared_ptr<ratchet::ActionComponent>>& ratchet::ActionComponent::GetChildren(void) {
    return this->_children;
}

bool ratchet::ActionComponent::IsInput(void) const {
    return true;
}

bool ratchet::ActionComponent::Initialize(void) {
    super::Initialize();
    // コンポーネントの初期化
    for (auto& com : _children) {
        com.second->Initialize();
    } // for
    return true;
}

bool ratchet::ActionComponent::Input(void) {
    if (_current_action) {
        _current_action->Input();
    } // if
    return false;
}

bool ratchet::ActionComponent::Update(float delta_time) {
    if (_current_action) {
        _current_action->Update(delta_time);
    } // if
    return false;
}

bool ratchet::ActionComponent::Release(void) {
    super::Release();
    for (auto& com : _children) {
        com.second->Release();
    } // for
    _children.clear();
    return true;
}

bool ratchet::ActionComponent::Start(void) {
    super::Activate();
    return true;
}

bool ratchet::ActionComponent::End(void) {
    super::Inactivate();
    return true;
}

void ratchet::ActionComponent::ChangeAction(std::string_view name) {
    auto it = _children.find(name.data());
    if (it != _children.end()) {
        _current_action = it->second;
    } // if
}

std::shared_ptr<ratchet::Component> ratchet::ActionComponent::Clone(void) {
    return std::make_shared<ratchet::ActionComponent>(*this);
}