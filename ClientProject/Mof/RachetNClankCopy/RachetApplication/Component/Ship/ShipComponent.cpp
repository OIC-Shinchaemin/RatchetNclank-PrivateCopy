#include "ShipComponent.h"

#include "../../Actor/Ship/Ship.h"
#include "../MotionComponent.h"
#include "../../Camera/FollowCameraController.h"
#include "../Collision/Object/ShipCollisionComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "ShipStateComponent.h"



rachet::ShipComponent::ShipComponent(int priority) :
    super(priority),
    _motion_com(),
    _state_com() {
}

rachet::ShipComponent::ShipComponent(const ShipComponent& obj) :
    super(obj),
    _motion_com(),
    _state_com() {
}

rachet::ShipComponent::~ShipComponent() {
}

std::string rachet::ShipComponent::GetType(void) const {
    return "ShipComponent";
}

bool rachet::ShipComponent::Initialize(void) {
    super::Initialize();
    _motion_com = super::GetOwner()->GetComponent<rachet::MotionComponent>();
    _state_com = super::GetOwner()->GetComponent<rachet::ShipStateComponent>();

    auto coll_com = super::GetOwner()->GetComponent<rachet::ShipCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               rachet::CollisionComponentType::kPlayerCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
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

bool rachet::ShipComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();

    if (pos.y > 10.0f) {
        super::GetOwner()->Notify("GameClear", super::GetOwner());
    } // if
    return true;
}

bool rachet::ShipComponent::Activate(void) {
    if (super::IsActive()) {
        return false;
    } // if
    super::Activate();
    /*
    if (auto motion_com = _motion_com.lock()) {
        motion_com->ChangeMotion(rachet::Ship::MotionType::Default);
        _timer.Initialize(7.0f, false);
    } // if
    */
    return true;
}


std::shared_ptr<rachet::Component> rachet::ShipComponent::Clone(void) {
    return std::make_shared<rachet::ShipComponent>(*this);
}