#include "MotionStateComponent.h"

#include "MotionComponent.h"


my::MotionStateComponent::MotionStateComponent(int priority) :
    super(priority),
    _state_machine(),
    _motion_com() {
}

my::MotionStateComponent::MotionStateComponent(const MotionStateComponent& obj) :
    super(obj),
    _state_machine(obj._state_machine),
    _motion_com() {
}

my::MotionStateComponent::~MotionStateComponent() {
}

void my::MotionStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::MotionStateComponent::GetType(void) const {
    return "MotionStateComponent";
}

bool my::MotionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();

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

bool my::MotionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool my::MotionStateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::MotionStateComponent::Clone(void) {
    return std::make_shared<my::MotionStateComponent>(*this);
}

void my::MotionStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}