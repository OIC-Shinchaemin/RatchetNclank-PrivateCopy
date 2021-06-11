#include "BoltComponent.h"

#include "../VelocityComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../Collision/Object/BoltCollisionComponent.h"
#include "../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../Component/Collision/Object/SightCollisionComponent.h"
#include "BoltActionStateComponent.h"


ratchet::BoltComponent::BoltComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

ratchet::BoltComponent::BoltComponent(const BoltComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

ratchet::BoltComponent::~BoltComponent() {
}

void ratchet::BoltComponent::SetActorParam(const ratchet::Bolt::Param& param) {
    this->_param = param;
}

std::string ratchet::BoltComponent::GetType(void) const {
    return "BoltComponent";
}

const ratchet::Bolt::Param& ratchet::BoltComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<ratchet::Actor> ratchet::BoltComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool ratchet::BoltComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::BoltActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<ratchet::BoltCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<ratchet::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Stay,
                                 ratchet::CollisionComponentType::kPlayerCollisionComponent,
                                 ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
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

bool ratchet::BoltComponent::Update(float delta_time) {
    return true;
}

bool ratchet::BoltComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BoltComponent::Clone(void) {
    return std::make_shared<ratchet::BoltComponent>(*this);
}