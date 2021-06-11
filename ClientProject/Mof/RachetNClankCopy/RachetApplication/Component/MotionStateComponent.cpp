#include "MotionStateComponent.h"

#include "MotionComponent.h"


rachet::MotionStateComponent::MotionStateComponent(int priority) :
    super(priority),
    _state_machine(),
    _motion_com() {
}

rachet::MotionStateComponent::MotionStateComponent(const MotionStateComponent& obj) :
    super(obj),
    _state_machine(obj._state_machine),
    _motion_com() {
}

rachet::MotionStateComponent::~MotionStateComponent() {
}

void rachet::MotionStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string rachet::MotionStateComponent::GetType(void) const {
    return "MotionStateComponent";
}

bool rachet::MotionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _motion_com = super::GetOwner()->GetComponent<rachet::MotionComponent>();

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

bool rachet::MotionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool rachet::MotionStateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::MotionStateComponent::Clone(void) {
    return std::make_shared<rachet::MotionStateComponent>(*this);
}

void rachet::MotionStateComponent::ChangeState(const std::string& name) {
    if (super::GetOwner()->GetTag() == "Enemy") {
        ;
    } // if
    _state_machine.ChangeState(name);
}