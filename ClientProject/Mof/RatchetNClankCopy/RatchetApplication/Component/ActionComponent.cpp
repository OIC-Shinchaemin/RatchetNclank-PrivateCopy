#include "ActionComponent.h"

#include "../Factory/FactoryManager.h"


ratchet::component::ActionComponent::ActionComponent(int priority) :
    super(priority),
    _current_action(),
    _children() {
}

ratchet::component::ActionComponent::ActionComponent(const ActionComponent& obj) :
    super(obj),
    _current_action(),
    _children() {
    this->_children.reserve(obj._children.size());
    for (auto& child : obj._children) {
        auto com = std::dynamic_pointer_cast<ratchet::component::ActionComponent>(child.second->Clone());
        this->_children.emplace(com->GetType().c_str(), com);
    } // for
}

ratchet::component::ActionComponent::~ActionComponent() {
}

void ratchet::component::ActionComponent::SetOwner(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    super::SetOwner(ptr);
    for (auto& com : _children) {
        com.second->SetOwner(ptr);
    } // for
}

void ratchet::component::ActionComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* children = "children";
    
    if (param.HasMember(children)) {
        _ASSERT_EXPR(param[children].IsArray(), L"�p�����[�^�̎w�肳�ꂽ�^�ł���܂���");
        _children.reserve(param[children].Size());
        for (int i = 0, n = param[children].Size(); i < n; i++) {
            auto& child = param[children][i];
            _ASSERT_EXPR(child.HasMember("type"), L"�^�C�v������܂���");
            _ASSERT_EXPR(child["type"].IsString(), L"�^�C�v���w�肳�ꂽ�^�ł���܂���");
            _ASSERT_EXPR(child.HasMember("paramater"), L"�p�����[�^������܂���");
            _ASSERT_EXPR(child["paramater"].IsObject(), L"�p�����[�^���w�肳�ꂽ�^�ł���܂���");

            auto& child_param = child["paramater"];
            std::string type = child["type"].GetString();

            auto com = ratchet::factory::FactoryManager::Singleton().CreateComponent(type.c_str(), child_param);
            _children.emplace(com->GetType(), std::dynamic_pointer_cast<ratchet::component::ActionComponent>(com));
        } // for
    } // if
}

std::string ratchet::component::ActionComponent::GetType(void) const {
    return "ActionComponent";
}

std::string_view ratchet::component::ActionComponent::GetStateType(void) const {
    return std::string_view();
}

const std::unordered_map<std::string, std::shared_ptr<ratchet::component::ActionComponent>>& ratchet::component::ActionComponent::GetChildren(void) {
    return this->_children;
}

bool ratchet::component::ActionComponent::IsInput(void) const {
    return true;
}

bool ratchet::component::ActionComponent::Initialize(void) {
    super::Initialize();
    // �R���|�[�l���g�̏�����
    for (auto& com : _children) {
        com.second->Initialize();
    } // for
    return true;
}

bool ratchet::component::ActionComponent::Input(void) {
    if (_current_action) {
        _current_action->Input();
    } // if
    return false;
}

bool ratchet::component::ActionComponent::Update(float delta_time) {
    if (_current_action) {
        _current_action->Update(delta_time);
    } // if
    return false;
}

bool ratchet::component::ActionComponent::Release(void) {
    super::Release();
    for (auto& com : _children) {
        com.second->Release();
    } // for
    _children.clear();
    return true;
}

bool ratchet::component::ActionComponent::Start(void) {
    super::Activate();
    return true;
}

bool ratchet::component::ActionComponent::End(void) {
    super::Inactivate();
    return true;
}

void ratchet::component::ActionComponent::ChangeAction(std::string_view name) {
    auto it = _children.find(name.data());
    if (it != _children.end()) {
        _current_action = it->second;
    } // if
}

std::shared_ptr<ratchet::component::Component> ratchet::component::ActionComponent::Clone(void) {
    return std::make_shared<ratchet::component::ActionComponent>(*this);
}