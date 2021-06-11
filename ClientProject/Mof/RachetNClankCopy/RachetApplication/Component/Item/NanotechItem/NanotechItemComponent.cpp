#include "NanotechItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/Object/CollisionComponentDefine.h"
#include "../../Collision/Object/NanotechItemCollisionComponent.h"
#include "../../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "NanotechItemActionStateComponent.h"


rachet::NanotechItemComponent::NanotechItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

rachet::NanotechItemComponent::NanotechItemComponent(const NanotechItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

rachet::NanotechItemComponent::~NanotechItemComponent() {
}

void rachet::NanotechItemComponent::SetActorParam(const rachet::NanotechItem::Param& param) {
    this->_param = param;
}

std::string rachet::NanotechItemComponent::GetType(void) const {
    return "NanotechItemComponent";
}

const rachet::NanotechItem::Param& rachet::NanotechItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<rachet::Actor> rachet::NanotechItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool rachet::NanotechItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<rachet::NanotechItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<rachet::NanotechItemCollisionComponent>();
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
            if (state_com->CanTransition(state::NanotechItemActionType::kGravitate)) {
                state_com->ChangeState(state::NanotechItemActionType::kGravitate);
                _player = in.target;
            } // if
        } // if
        return true;
    }));
    return true;
}

bool rachet::NanotechItemComponent::Update(float delta_time) {
    return true;
}

bool rachet::NanotechItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::NanotechItemComponent::Clone(void) {
    return std::make_shared<rachet::NanotechItemComponent>(*this);
}