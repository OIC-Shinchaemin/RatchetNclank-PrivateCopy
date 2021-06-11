#include "ShipComponent.h"

#include "../../Actor/Vehicle/Ship.h"
#include "../MotionComponent.h"
#include "../../Camera/FollowCameraController.h"
#include "../Collision/Object/ShipCollisionComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "ShipStateComponent.h"



ratchet::ShipComponent::ShipComponent(int priority) :
    super(priority),
    _motion_com(),
    _state_com() {
}

ratchet::ShipComponent::ShipComponent(const ShipComponent& obj) :
    super(obj),
    _motion_com(),
    _state_com() {
}

ratchet::ShipComponent::~ShipComponent() {
}

std::string ratchet::ShipComponent::GetType(void) const {
    return "ShipComponent";
}

bool ratchet::ShipComponent::Initialize(void) {
    super::Initialize();
    _motion_com = super::GetOwner()->GetComponent<ratchet::MotionComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::ShipStateComponent>();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::ShipCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        this->Activate();

        if (auto state_com = _state_com.lock()) {
            
            if (state_com->CanTransition(state::ShipActionStateType::kShipActionTakeoffState)) {
                state_com->ChangeState(state::ShipActionStateType::kShipActionTakeoffState);
            } // if
        } // if

        return true;
    }));

    return true;
}

bool ratchet::ShipComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();

    if (pos.y > 10.0f) {
        super::GetOwner()->Notify("GameClear", super::GetOwner());
    } // if
    return true;
}

bool ratchet::ShipComponent::Activate(void) {
    if (super::IsActive()) {
        return false;
    } // if
    super::Activate();
    /*
    if (auto motion_com = _motion_com.lock()) {
        motion_com->ChangeMotion(ratchet::Ship::MotionType::Default);
        _timer.Initialize(7.0f, false);
    } // if
    */
    return true;
}


std::shared_ptr<ratchet::component::Component> ratchet::ShipComponent::Clone(void) {
    return std::make_shared<ratchet::ShipComponent>(*this);
}