#include "PlayerDamageComponent.h"

#include "../HpComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../Collision/Object/PlayerCollisionComponent.h"


my::PlayerDamageComponent::PlayerDamageComponent(int priority) :
    super(priority),
    _damage_value(),
    _damage_angle(),
    _hp_com() {
}

my::PlayerDamageComponent::PlayerDamageComponent(const PlayerDamageComponent& obj) :
    super(obj),
    _damage_value(),
    _damage_angle(),
    _hp_com() {
}

my::PlayerDamageComponent::~PlayerDamageComponent() {
}

std::string my::PlayerDamageComponent::GetType(void) const {
    return "PlayerDamageComponent";
}

std::string_view my::PlayerDamageComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDamageState;
}

bool my::PlayerDamageComponent::Initialize(void) {
    super::Initialize();
    _hp_com = super::GetOwner()->GetComponent<my::HpComponent>();

    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kEnemyAttackCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        if (super::CanTransitionActionState(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_angle = in.angle;
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDamageState);
        } // if
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kEnemyBulletCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        if (super::CanTransitionActionState(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_angle = in.angle;
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDamageState);
        } // if
        return true;
    }));
    return true;
}

bool my::PlayerDamageComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool my::PlayerDamageComponent::Release(void) {
    super::Release();
    _hp_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerDamageComponent::Clone(void) {
    return std::make_shared<my::PlayerDamageComponent>(*this);
}

bool my::PlayerDamageComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionDamageState);

    auto velocity_com = super::GetVelocityComponent();
    auto accele = Mof::CVector3(0.0f, 0.0f, -10.0f);
    accele.RotateAround(math::vec3::kZero, _damage_angle);
    velocity_com->SetVelocity(math::vec3::kZero);
    velocity_com->AddVelocityForce(accele);

    if (auto hp_com = _hp_com.lock()) {
        hp_com->Damage(_damage_value);
        if (hp_com->GetHp() == 0) {
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDeadState);
        } // if
        _damage_value = 0;
    } // if
    return true;
}