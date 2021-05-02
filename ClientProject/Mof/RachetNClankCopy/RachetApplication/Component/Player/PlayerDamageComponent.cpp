#include "PlayerDamageComponent.h"

#include "../Collision/Object/CollisionComponentDefine.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../State/PlayerMotion/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../HpComponent.h"
#include "../Player/PlayerStateComponent.h"
#include "../Collision/Object/PlayerCollisionComponent.h"


my::PlayerDamageComponent::PlayerDamageComponent(int priority) :
    super(priority),
    _damage_value(),
    _damage_angle(),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com() {
}

my::PlayerDamageComponent::PlayerDamageComponent(const PlayerDamageComponent& obj) :
    super(obj._priority),
    _damage_value(),
    _damage_angle(),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com(),
    _state_com() {
}

my::PlayerDamageComponent::~PlayerDamageComponent() {
}

std::string my::PlayerDamageComponent::GetType(void) const {
    return "PlayerDamageComponent";
}

bool my::PlayerDamageComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _hp_com = super::GetOwner()->GetComponent<my::HpComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();

    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kEnemyAttackCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        auto state_com = _state_com.lock();
        if (state_com->CanTransition(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_angle = in.angle;
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionDamageState);
        } // if
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kEnemyBulletCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        auto state_com = _state_com.lock();
        if (state_com->CanTransition(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_angle = in.angle;
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionDamageState);
        } // if
        return true;
    }));
    return true;
}

bool my::PlayerDamageComponent::Update(float delta_time) {
    if (auto motion_com = _motion_com.lock()) {
        auto state_com = _state_com.lock();
        if (motion_com->IsEndMotion()) {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
        } // if
    } // if
    return true;
}

bool my::PlayerDamageComponent::Release(void) {
    super::Release();
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
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionDamageState);
    } // if
    if (auto velocity_com = _velocity_com.lock()) {
        auto accele = Mof::CVector3(0.0f, 0.0f, -10.0f);

        accele.RotateAround(math::vec3::kZero, _damage_angle);
        velocity_com->SetVelocity(math::vec3::kZero);
        velocity_com->AddVelocityForce(accele);
    } // if
    if (auto hp_com = _hp_com.lock()) {
        hp_com->Damage(_damage_value);
        if (hp_com->GetHp() == 0) {
            auto state_com = _state_com.lock();
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionDeadState);
        } // if
        _damage_value = 0;
    } // if
    return true;
}