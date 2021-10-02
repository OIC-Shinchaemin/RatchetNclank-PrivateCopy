#include "InvincibleComponent.h"


ratchet::component::InvincibleComponent::InvincibleComponent(int priority) :
    super(priority),
    _invincible() ,
    _time(1.0f){
}

ratchet::component::InvincibleComponent::InvincibleComponent(const InvincibleComponent& obj) :
    super(obj),
    _invincible(),
    _time(obj._time){
}

ratchet::component::InvincibleComponent::~InvincibleComponent() {
}

void ratchet::component::InvincibleComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);

    const char* time = "time";
    if (param.HasMember(time)) {
        _ASSERT_EXPR(param[time].IsFloat(), L"パラメータの指定された型でありません");
        _time = param[time].IsFloat();
    } // if
}

std::string ratchet::component::InvincibleComponent::GetType(void) const {
    return "InvincibleComponent";
}

bool ratchet::component::InvincibleComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::InvincibleComponent::Update(float delta_time) {
    if (_invincible.Tick(delta_time)) {
        super::Inactivate();
    } // if
    return true;
}

bool ratchet::component::InvincibleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::InvincibleComponent::Clone(void) {
    return std::make_shared<ratchet::component::InvincibleComponent>(*this);
}

bool ratchet::component::InvincibleComponent::Activate(void) {
    if (this->IsActive()) {
        return false;
    } // if

    super::Activate();
    _invincible.Initialize(_time, false);
    return true;
}