#include "ShipComponent.h"

#include "../../Actor/Vehicle/Ship.h"
#include "../MotionComponent.h"
#include "../../Camera/FollowCameraController.h"
#include "../Collision/Object/ShipCollisionComponent.h"
#include "../Collision/CollisionComponentDefine.h"
#include "ShipStateComponent.h"



ratchet::component::ship::ShipComponent::ShipComponent(int priority) :
    super(priority),
    _motion_com(),
    _state_com() {
}

ratchet::component::ship::ShipComponent::ShipComponent(const ShipComponent& obj) :
    super(obj),
    _motion_com(),
    _state_com() {
}

ratchet::component::ship::ShipComponent::~ShipComponent() {
}

std::string ratchet::component::ship::ShipComponent::GetType(void) const {
    return "ShipComponent";
}

bool ratchet::component::ship::ShipComponent::Initialize(void) {
    super::Initialize();
    _motion_com = super::GetOwner()->GetComponent<ratchet::component::MotionComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::ship::ShipStateComponent>();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::ShipCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
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

bool ratchet::component::ship::ShipComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();

    if (pos.y > 10.0f) {
        super::GetOwner()->Notify("GameClear", super::GetOwner());
    } // if
    return true;
}

bool ratchet::component::ship::ShipComponent::Activate(void) {
    if (super::IsActive()) {
        return false;
    } // if
    super::Activate();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::ship::ShipComponent::Clone(void) {
    return std::make_shared<ratchet::component::ship::ShipComponent>(*this);
}