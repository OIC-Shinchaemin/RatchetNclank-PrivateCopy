#include "NanotechItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/Object/CollisionComponentDefine.h"
#include "../../Collision/Object/NanotechItemCollisionComponent.h"
#include "../../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "NanotechItemActionStateComponent.h"


ratchet::component::item::nanotechitem::NanotechItemComponent::NanotechItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

ratchet::component::item::nanotechitem::NanotechItemComponent::NanotechItemComponent(const NanotechItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

ratchet::component::item::nanotechitem::NanotechItemComponent::~NanotechItemComponent() {
}

void ratchet::component::item::nanotechitem::NanotechItemComponent::SetActorParam(const ratchet::actor::item::NanotechItem::Param& param) {
    this->_param = param;
}

std::string ratchet::component::item::nanotechitem::NanotechItemComponent::GetType(void) const {
    return "NanotechItemComponent";
}

const ratchet::actor::item::NanotechItem::Param& ratchet::component::item::nanotechitem::NanotechItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<ratchet::actor::Actor> ratchet::component::item::nanotechitem::NanotechItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool ratchet::component::item::nanotechitem::NanotechItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::nanotechitem::NanotechItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::NanotechItemCollisionComponent>();
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
            if (state_com->CanTransition(state::NanotechItemActionType::kGravitate)) {
                state_com->ChangeState(state::NanotechItemActionType::kGravitate);
                _player = in.target;
            } // if
        } // if
        return true;
    }));
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::nanotechitem::NanotechItemComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::nanotechitem::NanotechItemComponent>(*this);
}