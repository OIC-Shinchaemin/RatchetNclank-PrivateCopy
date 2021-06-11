#include "BoltComponent.h"

#include "../VelocityComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../Collision/Object/BoltCollisionComponent.h"
#include "../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../Component/Collision/Object/SightCollisionComponent.h"
#include "BoltActionStateComponent.h"


rachet::BoltComponent::BoltComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

rachet::BoltComponent::BoltComponent(const BoltComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

rachet::BoltComponent::~BoltComponent() {
}

void rachet::BoltComponent::SetActorParam(const rachet::Bolt::Param& param) {
    this->_param = param;
}

std::string rachet::BoltComponent::GetType(void) const {
    return "BoltComponent";
}

const rachet::Bolt::Param& rachet::BoltComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<rachet::Actor> rachet::BoltComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool rachet::BoltComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<rachet::BoltActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<rachet::BoltCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               rachet::CollisionComponentType::kPlayerCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<rachet::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Stay,
                                 rachet::CollisionComponentType::kPlayerCollisionComponent,
                                 rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        if (auto state_com = _state_com.lock()) {
            if (state_com->CanTransition(state::BoltActionType::kGravitate)) {
                state_com->ChangeState(state::BoltActionType::kGravitate);
                _player = in.target;
            } // if
        } // if
        return true;
    }));
    return true;
}

bool rachet::BoltComponent::Update(float delta_time) {
    return true;
}

bool rachet::BoltComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BoltComponent::Clone(void) {
    return std::make_shared<rachet::BoltComponent>(*this);
}