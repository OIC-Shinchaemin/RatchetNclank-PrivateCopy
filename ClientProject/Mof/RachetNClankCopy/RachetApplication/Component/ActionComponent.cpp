#include "ActionComponent.h"

#include "../Factory/FactoryManager.h"


my::ActionComponent::ActionComponent(int priority) :
    super(priority),
    _current_action(),
    _children() {
}

my::ActionComponent::ActionComponent(const ActionComponent& obj) :
    super(obj),
    _current_action(),
    _children() {
    this->_children.reserve(obj._children.size());
    for (auto& child : obj._children) {
        auto com = std::dynamic_pointer_cast<my::ActionComponent>(child.second->Clone());
        this->_children.emplace(com->GetType().c_str(), com);
    } // for
}

my::ActionComponent::~ActionComponent() {
}

void my::ActionComponent::SetOwner(const std::shared_ptr<my::Actor>& ptr) {
    super::SetOwner(ptr);
    for (auto& com : _children) {
        com.second->SetOwner(ptr);
    } // for
}

void my::ActionComponent::SetParam(const rapidjson::Value& param) {
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

            auto com = my::FactoryManager::Singleton().CreateComponent(type.c_str(), child_param);
            _children.emplace(com->GetType(), std::dynamic_pointer_cast<my::ActionComponent>(com));
        } // for
    } // if
}

std::string my::ActionComponent::GetType(void) const {
    return "ActionComponent";
}

std::string_view my::ActionComponent::GetStateType(void) const {
    return std::string_view();
}

const std::unordered_map<std::string, std::shared_ptr<my::ActionComponent>>& my::ActionComponent::GetChildren(void) {
    return this->_children;
}

bool my::ActionComponent::IsInput(void) const {
    return true;
}

bool my::ActionComponent::Initialize(void) {
    super::Initialize();
    // コンポーネントの初期化
    for (auto& com : _children) {
        com.second->Initialize();
    } // for
    return true;
}

bool my::ActionComponent::Input(void) {
    if (_current_action) {
        _current_action->Input();
    } // if
    return false;
}

bool my::ActionComponent::Update(float delta_time) {
    if (_current_action) {
        _current_action->Update(delta_time);
    } // if
    return false;
}

bool my::ActionComponent::Release(void) {
    super::Release();
    for (auto& com : _children) {
        com.second->Release();
    } // for
    _children.clear();
    return true;
}

bool my::ActionComponent::Start(void) {
    super::Activate();
    return true;
}

bool my::ActionComponent::End(void) {
    super::Inactivate();
    return true;
}

void my::ActionComponent::ChangeAction(std::string_view name) {
    auto it = _children.find(name.data());
    if (it != _children.end()) {
        _current_action = it->second;
    } // if
}

std::shared_ptr<my::Component> my::ActionComponent::Clone(void) {
    return std::make_shared<my::ActionComponent>(*this);
}