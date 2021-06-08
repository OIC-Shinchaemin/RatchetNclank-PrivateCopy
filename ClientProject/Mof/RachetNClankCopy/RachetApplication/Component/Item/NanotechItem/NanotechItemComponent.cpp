#include "NanotechItemComponent.h"

#include "../../VelocityComponent.h"
#include "../../Collision/Object/CollisionComponentDefine.h"
#include "../../Collision/Object/NanotechItemCollisionComponent.h"
#include "../../../Component/Collision/Object/CollisionComponentDefine.h"
#include "../../../Component/Collision/Object/SightCollisionComponent.h"
#include "NanotechItemActionStateComponent.h"


my::NanotechItemComponent::NanotechItemComponent(int priority) :
    super(priority),
    _param(),
    _player(),
    _state_com() {
}

my::NanotechItemComponent::NanotechItemComponent(const NanotechItemComponent& obj) :
    super(obj),
    _param(),
    _player(),
    _state_com() {
}

my::NanotechItemComponent::~NanotechItemComponent() {
}

void my::NanotechItemComponent::SetActorParam(const my::NanotechItem::Param& param) {
    this->_param = param;
}

std::string my::NanotechItemComponent::GetType(void) const {
    return "NanotechItemComponent";
}

const my::NanotechItem::Param& my::NanotechItemComponent::GetActorParam(void) const {
    return this->_param;
}

std::shared_ptr<my::Actor> my::NanotechItemComponent::GetPlayer(void) const {
    if (auto ptr = _player.lock()) {
        return ptr;
    } // if
    return nullptr;
}

bool my::NanotechItemComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<my::NanotechItemActionStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    velocity_com->SetGravity(0.8f);

    auto coll_com = super::GetOwner()->GetComponent<my::NanotechItemCollisionComponent>();
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
            if (state_com->CanTransition(state::NanotechItemActionType::kGravitate)) {
                state_com->ChangeState(state::NanotechItemActionType::kGravitate);
                _player = in.target;
            } // if
        } // if
        return true;
    }));
    return true;
}

bool my::NanotechItemComponent::Update(float delta_time) {
    return true;
}

bool my::NanotechItemComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::NanotechItemComponent::Clone(void) {
    return std::make_shared<my::NanotechItemComponent>(*this);
}