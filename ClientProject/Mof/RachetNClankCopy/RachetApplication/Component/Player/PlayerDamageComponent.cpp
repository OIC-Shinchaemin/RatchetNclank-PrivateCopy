#include "PlayerDamageComponent.h"

#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../HpComponent.h"
#include "../Player/PlayerIdleComponent.h"
#include "../Player/PlayerStateComponent.h"
#include "../InvincibleComponent.h"
#include "../Collision/Object/PlayerCollisionComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"


my::PlayerDamageComponent::PlayerDamageComponent(int priority) :
    super(priority),
    _damage_angle(),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com(),
    _invincible_com(),
    _idle_com() {
}

my::PlayerDamageComponent::PlayerDamageComponent(const PlayerDamageComponent& obj) :
    super(obj._priority),
    _damage_angle(),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com(),
    _idle_com(),
    _invincible_com(),
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
    _idle_com = super::GetOwner()->GetComponent<my::PlayerIdleComponent>();
    _invincible_com = super::GetOwner()->GetComponent<my::InvincibleComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();

    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kEnemyAttackCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {

        this->Start();
        _damage_angle = in.angle;
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kEnemyBulletCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        this->Start();
        _damage_angle = in.angle;
        return true;
    }));
    return true;
}

bool my::PlayerDamageComponent::Update(float delta_time) {
    puts("PlayerDamageComponent");
    if (auto motion_com = _motion_com.lock()) {
        auto state_com = _state_com.lock();

        if (motion_com->IsEndMotion()) {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
            /*
            if (auto invincible_com = _invincible_com.lock()) {
                invincible_com->Start();
            } // if
            */
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
        puts("false");
        return false;
    } // if
    /*
    if (auto invincible_com = _invincible_com.lock()) {
        if (invincible_com->IsActive()) {
            return false;
        } // if
    } // if
    */
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionDamageState");
    } // if
    if (auto hp_com = _hp_com.lock()) {
        hp_com->Damage(1);
    } // if
    if (auto velocity_com = _velocity_com.lock()) {
        auto accele = Mof::CVector3(0.0f, 0.0f, -10.0f);
        accele.RotateAround(Mof::CVector3(), _damage_angle);
        velocity_com->AddVelocityForce(accele);
    } // if
    return true;
}