#include "EnemyDamageComponent.h"

#include "../Collision/Object/CollisionComponentDefine.h"
#include "../../State/EnemyAction/EnemyActionStateDefine.h"
#include "../../State/EnemyMotion/EnemyMotionStateDefine.h"
#include "EnemyComponent.h"
#include "EnemyStateComponent.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../HpComponent.h"
#include "../Collision/Object/EnemyCollisionComponent.h"


void my::EnemyDamageComponent::CollisionAction(const my::CollisionInfo& in) {
    if (auto state_com = _state_com.lock()) {
        if (state_com->CanTransition(state::EnemyActionStateType::kEnemyActionDamageState)) {
            state_com->ChangeState(state::EnemyActionStateType::kEnemyActionDamageState);
            _damage_angle.y = in.angle.y;
        } // if
    } // if
    if (auto velocity_com = _velocity_com.lock()) {
        Mof::CVector3 accele = Mof::CVector3(0.0f, 0.0f, -in.speed);
        accele.RotateAround(math::vec3::kZero, -_damage_angle);
        velocity_com->AddVelocityForce(accele);
    } // if
    auto rotate = super::GetOwner()->GetRotate();
    rotate.y = _damage_angle.y;
    super::GetOwner()->SetRotate(rotate);
}

my::EnemyDamageComponent::EnemyDamageComponent(int priority) :
    super(priority),
    _damage_value(0),
    _damage_angle(),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com(),
    _enemy_com(),
    _state_com() {
}

my::EnemyDamageComponent::EnemyDamageComponent(const EnemyDamageComponent& obj) :
    super(obj._priority),
    _damage_value(0),
    _damage_angle(),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com(),
    _state_com() {
}

my::EnemyDamageComponent::~EnemyDamageComponent() {
}

std::string my::EnemyDamageComponent::GetType(void) const {
    return "EnemyDamageComponent";
}

bool my::EnemyDamageComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _hp_com = super::GetOwner()->GetComponent<my::HpComponent>();
    _enemy_com = super::GetOwner()->GetComponent<my::EnemyComponent>();
    _state_com = super::GetOwner()->GetComponent<my::EnemyStateComponent>();

    auto coll_com = super::GetOwner()->GetComponent<my::EnemyCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Stay,
                               my::CollisionComponentType::kPlayerCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        auto enemy_com = _enemy_com.lock();
        auto target = in.target.lock();
        
        Mof::CVector3 vec = super::GetOwner()->GetPosition() - target->GetPosition();
        auto length = (enemy_com->GetVolume() * 2.0f) - vec.Length();
        vec.Normal(vec);
        // —£‚ê‚é
        auto diff = vec * length * 0.5f; diff.y = 0.0f;

        auto pos = super::GetOwner()->GetPosition();
        super::GetOwner()->SetPosition(pos + diff);
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kPlayerMeleeAttackCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        _damage_value = 1;
        this->CollisionAction(in);
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kPyrocitorBulletCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        _damage_value = 1;
        this->CollisionAction(in);
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kBlasterBulletCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        _damage_value = 1;
        this->CollisionAction(in);
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               my::CollisionComponentType::kBombGloveEffectCollisionComponent,
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        _damage_value = 2;
        this->CollisionAction(in);
        return true;
    }));
    return true;
}

bool my::EnemyDamageComponent::Update(float delta_time) {
    if (auto motion_com = _motion_com.lock()) {
        auto state_com = _state_com.lock();
        if (motion_com->IsEndMotion()) {
            if (auto hp_com = _hp_com.lock()) {
                if (hp_com->GetHp() == 0) {
                    super::GetOwner()->End();
                } // if
            } // if

            state_com->ChangeState(state::EnemyActionStateType::kEnemyActionIdleState);
        } // if
    } // if
    return true;
}

bool my::EnemyDamageComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyDamageComponent::Clone(void) {
    return std::make_shared<my::EnemyDamageComponent>(*this);
}

bool my::EnemyDamageComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::EnemyMotionStateType::kEnemyMotionDamageState);
    } // if
    if (auto motion_com = _motion_com.lock()) {
        motion_com->AddTimer(0.6f);
    } // if
    /*

    if (auto velocity_com = _velocity_com.lock()) {
        float speed = 2.0f;
        float angle_y = _damage_angle.y;
        auto accele = Mof::CVector3(0.0f, angle_y * speed, 0.0f);
        velocity_com->AddAngularVelocityForce(accele);

        auto rotate = super::GetOwner()->GetRotate();
        rotate.y = _damage_angle.y;
    } // if
    */

    if (auto hp_com = _hp_com.lock()) {
        hp_com->Damage(_damage_value);
        _damage_value = 0;
    } // if
    return true;
}