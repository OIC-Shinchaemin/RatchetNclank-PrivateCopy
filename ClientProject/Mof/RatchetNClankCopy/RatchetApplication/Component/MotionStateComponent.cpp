#include "MotionStateComponent.h"

#include "MotionComponent.h"


ratchet::component::MotionStateComponent::MotionStateComponent(int priority) :
    super(priority),
    _state_machine(),
    _motion_com() {
}

ratchet::component::MotionStateComponent::MotionStateComponent(const MotionStateComponent& obj) :
    super(obj),
    _state_machine(obj._state_machine),
    _motion_com() {
}

ratchet::component::MotionStateComponent::~MotionStateComponent() {
}

void ratchet::component::MotionStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string ratchet::component::MotionStateComponent::GetType(void) const {
    return "MotionStateComponent";
}

bool ratchet::component::MotionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _motion_com = super::GetOwner()->GetComponent<ratchet::component::MotionComponent>();

    using Param = state::MotionState::Param;
    if (auto motion_com = _motion_com.lock()) {
        std::string_view default_state;
        auto info_map = motion_com->GetMotionInfoMap();
        for (auto& info : *info_map) {
            if (info.first == 0) {
                default_state = info.second.state;
            } // if
            this->RegisterState(Param(info.second.state, info.second.name,
                                      info.first, info.second.speed, 
                                      info.second.loop, info.second.same));
        } // for
        _state_machine.ChangeState(default_state.data());
    } // if
    return true;
}

bool ratchet::component::MotionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool ratchet::component::MotionStateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::MotionStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::MotionStateComponent>(*this);
}

void ratchet::component::MotionStateComponent::ChangeState(const std::string& name) {
    if (super::GetOwner()->GetTag() == "Enemy") {
        ;
    } // if
    _state_machine.ChangeState(name);
}