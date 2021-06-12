#include "BoltComponent.h"

#include "../VelocityComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../Collision/Object/BoltCollisionComponent.h"
#include "../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../Component/Collision/Object/SightCollisionComponent.h"
#include "BoltActionStateComponent.h"


ratchet::component::item::BoltComponent::BoltComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

ratchet::component::item::BoltComponent::BoltComponent(const BoltComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

ratchet::component::item::BoltComponent::~BoltComponent() {
}

void ratchet::component::item::BoltComponent::SetActorParam(const ratchet::actor::item::Bolt::Param& param) {
    this->_param = param;
}

std::string ratchet::component::item::BoltComponent::GetType(void) const {
    return "BoltComponent";
}

const ratchet::actor::item::Bolt::Param& ratchet::component::item::BoltComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<ratchet::actor::Actor> ratchet::component::item::BoltComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool ratchet::component::item::BoltComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::BoltActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::BoltCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<ratchet::component::collision::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                                 ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent,
                                 ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
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

bool ratchet::component::item::BoltComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::item::BoltComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::BoltComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::BoltComponent>(*this);
}