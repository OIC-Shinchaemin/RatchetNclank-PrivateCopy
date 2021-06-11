#include "NanotechItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/Object/CollisionComponentDefine.h"
#include "../../Collision/Object/NanotechItemCollisionComponent.h"
#include "../../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "NanotechItemActionStateComponent.h"


ratchet::NanotechItemComponent::NanotechItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

ratchet::NanotechItemComponent::NanotechItemComponent(const NanotechItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

ratchet::NanotechItemComponent::~NanotechItemComponent() {
}

void ratchet::NanotechItemComponent::SetActorParam(const ratchet::actor::item::NanotechItem::Param& param) {
    this->_param = param;
}

std::string ratchet::NanotechItemComponent::GetType(void) const {
    return "NanotechItemComponent";
}

const ratchet::actor::item::NanotechItem::Param& ratchet::NanotechItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<ratchet::actor::Actor> ratchet::NanotechItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool ratchet::NanotechItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::NanotechItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<ratchet::NanotechItemCollisionComponent>();
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
            if (state_com->CanTransition(state::NanotechItemActionType::kGravitate)) {
                state_com->ChangeState(state::NanotechItemActionType::kGravitate);
                _player = in.target;
            } // if
        } // if
        return true;
    }));
    return true;
}

bool ratchet::NanotechItemComponent::Update(float delta_time) {
    return true;
}

bool ratchet::NanotechItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::NanotechItemComponent::Clone(void) {
    return std::make_shared<ratchet::NanotechItemComponent>(*this);
}