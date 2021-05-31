#include "BoltComponent.h"

#include "../VelocityComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../Collision/Object/BoltCollisionComponent.h"
#include "../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../Component/Collision/Object/SightCollisionComponent.h"
#include "BoltActionStateComponent.h"


my::BoltComponent::BoltComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

my::BoltComponent::BoltComponent(const BoltComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

my::BoltComponent::~BoltComponent() {
}

void my::BoltComponent::SetActorParam(const my::Bolt::Param& param) {
    this->_param = param;
}

std::string my::BoltComponent::GetType(void) const {
    return "BoltComponent";
}

const my::Bolt::Param& my::BoltComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<my::Actor> my::BoltComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool my::BoltComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<my::BoltActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<my::BoltCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kPlayerCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    auto sight_coll = super::GetOwner()->GetComponent<my::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Stay,
                                 my::CollisionComponentType::kPlayerCollisionComponent,
                                 my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
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