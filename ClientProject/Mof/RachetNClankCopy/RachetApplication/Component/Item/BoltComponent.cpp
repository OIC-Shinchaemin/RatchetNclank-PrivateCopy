#include "BoltComponent.h"

#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../Collision/Object/BoltCollisionComponent.h"


my::BoltComponent::BoltComponent(int priority) :
    super(priority){
}

my::BoltComponent::BoltComponent(const BoltComponent& obj) :
    super(obj){
}

my::BoltComponent::~BoltComponent() {
}

std::string my::BoltComponent::GetType(void) const {
    return "BoltComponent";
}

bool my::BoltComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    /*
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();

    velocity_com->SetGravity(9.8f);
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    */

    auto coll_com = super::GetOwner()->GetComponent<my::BoltCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kPlayerCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool my::BoltComponent::Update(float delta_time) {
    return true;
}

bool my::BoltComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BoltComponent::Clone(void) {
    return std::make_shared<my::BoltComponent>(*this);
}