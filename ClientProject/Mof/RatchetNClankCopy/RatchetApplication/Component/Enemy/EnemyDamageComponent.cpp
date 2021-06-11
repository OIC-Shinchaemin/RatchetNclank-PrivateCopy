#include "EnemyDamageComponent.h"

#include "../Collision/Object/CollisionComponentDefine.h"
#include "../../State/EnemyActionStateDefine.h"
#include "../../State/EnemyMotionStateDefine.h"
#include "EnemyComponent.h"
#include "EnemyStateComponent.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../HpComponent.h"
#include "../Collision/Object/EnemyCollisionComponent.h"


void ratchet::EnemyDamageComponent::CollisionAction(const ratchet::CollisionInfo& in) {
    if (auto state_com = _state_com.lock()) {
        if (state_com->CanTransition(state::EnemyActionStateType::kEnemyActionDamageState)) {
            state_com->ChangeState(state::EnemyActionStateType::kEnemyActionDamageState);
            _damage_angle.y = in.angle.y;
            _damage_speed = in.speed;
        } // if
    } // if
}

ratchet::EnemyDamageComponent::EnemyDamageComponent(int priority) :
    super(priority),
    _damage_value(0),
    _damage_angle(),
    _damage_speed(0.0f),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com(),
    _ENEMY_com(),
    _state_com() {
}

ratchet::EnemyDamageComponent::EnemyDamageComponent(const EnemyDamageComponent& obj) :
    super(obj),
    _damage_value(0),
    _damage_angle(),
    _damage_speed(0.0f),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _hp_com(),
    _state_com() {
}

ratchet::EnemyDamageComponent::~EnemyDamageComponent() {
}

std::string ratchet::EnemyDamageComponent::GetType(void) const {
    return "EnemyDamageComponent";
}

std::string_view ratchet::EnemyDamageComponent::GetStateType(void) const {
    return state::EnemyActionStateType::kEnemyActionDamageState;
}

bool ratchet::EnemyDamageComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<ratchet::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::MotionStateComponent>();
    _hp_com = super::GetOwner()->GetComponent<ratchet::HpComponent>();
    _ENEMY_com = super::GetOwner()->GetComponent<ratchet::EnemyComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::EnemyStateComponent>();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::EnemyCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::CollisionComponentType::kPlayerCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        auto ENEMY_com = _ENEMY_com.lock();
        auto target = in.target.lock();
        
        Mof::CVector3 vec = super::GetOwner()->GetPosition() - target->GetPosition();
        auto length = (ENEMY_com->GetVolume() * 2.0f) - vec.Length();
        vec.Normal(vec);
        // —£‚ê‚é
        auto diff = vec * length * 0.5f; diff.y = 0.0f;

        auto pos = super::GetOwner()->GetPosition();
        super::GetOwner()->SetPosition(pos + diff);
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kOmniWrenchCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        _damage_value = 1;
        this->CollisionAction(in);
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kPyrocitorBulletCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        _damage_value = 1;
        this->CollisionAction(in);
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kBlasterBulletCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        _damage_value = 1;
        this->CollisionAction(in);
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kBombGloveEffectCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        _damage_value = 2;
        this->CollisionAction(in);
        return true;
    }));
    return true;
}

bool ratchet::EnemyDamageComponent::Update(float delta_time) {
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

bool ratchet::EnemyDamageComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::EnemyDamageComponent::Clone(void) {
    return std::make_shared<ratchet::EnemyDamageComponent>(*this);
}

bool ratchet::EnemyDamageComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::EnemyMotionStateType::kEnemyMotionDamageState);
        if (auto motion_com = _motion_com.lock()) {
            motion_com->AddTimer(0.6f);
        } // if
    } // if

    if (auto hp_com = _hp_com.lock()) {
        hp_com->Damage(_damage_value);
        _damage_value = 0;
    } // if
    if (auto velocity_com = _velocity_com.lock()) {
        Mof::CVector3 accele = Mof::CVector3(0.0f, 0.0f, -_damage_speed);
        accele.RotateAround(math::vec3::kZero, -_damage_angle);
        velocity_com->AddVelocityForce(accele);
    } // if
    auto rotate = super::GetOwner()->GetRotate();
    rotate.y = _damage_angle.y;
    super::GetOwner()->SetRotate(rotate);
    return true;
}