#include "PlayerDamageComponent.h"

#include "../HpComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../Collision/Object/PlayerCollisionComponent.h"


void rachet::PlayerDamageComponent::DamegeAccele(void) {
    auto velocity_com = super::GetVelocityComponent();
    auto accele = Mof::CVector3(0.0f, 0.0f, -_damage_speed);
    accele.RotateAround(math::vec3::kZero, _damage_angle);
    velocity_com->SetVelocity(math::vec3::kZero);
    velocity_com->AddVelocityForce(accele);
}

void rachet::PlayerDamageComponent::Damege(void) {
    if (auto hp_com = _hp_com.lock()) {
        hp_com->Damage(_damage_value);
        if (hp_com->GetHp() == 0) {
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDeadState);
        } // if
        else {
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDamageState);
        } // else
        _damage_value = 0;
    } // if
}

void rachet::PlayerDamageComponent::Heal(void) {
    if (auto hp_com = _hp_com.lock()) {
        hp_com->Heal(1);
    } // if
}

rachet::PlayerDamageComponent::PlayerDamageComponent(int priority) :
    super(priority),
    _damage_value(),
    _damage_speed(),
    _damage_angle(),
    _hp_com() {
}

rachet::PlayerDamageComponent::PlayerDamageComponent(const PlayerDamageComponent& obj) :
    super(obj),
    _damage_value(),
    _damage_speed(),
    _damage_angle(),
    _hp_com() {
}

rachet::PlayerDamageComponent::~PlayerDamageComponent() {
}

std::string rachet::PlayerDamageComponent::GetType(void) const {
    return "PlayerDamageComponent";
}

std::string_view rachet::PlayerDamageComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDamageState;
}

bool rachet::PlayerDamageComponent::Initialize(void) {
    super::Initialize();
    _hp_com = super::GetOwner()->GetComponent<rachet::HpComponent>();

    auto coll_com = super::GetOwner()->GetComponent<rachet::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               rachet::CollisionComponentType::kEnemyMeleeAttackCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        if (super::CanTransitionActionState(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_speed = in.speed;
            this->_damage_angle = in.angle;
            this->DamegeAccele();
            this->Damege();
        } // if
        return true;
    }));

    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               rachet::CollisionComponentType::kNanotechItemCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        this->Heal();
        return true;
    }));


    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               rachet::CollisionComponentType::kEnemyBulletCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        if (super::CanTransitionActionState(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_speed = in.speed;
            this->_damage_angle = in.angle;
            this->DamegeAccele();
            this->Damege();
            //super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDamageState);
        } // if
        return true;
    }));
    return true;
}

bool rachet::PlayerDamageComponent::Input(void) {
    return false;
}

bool rachet::PlayerDamageComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool rachet::PlayerDamageComponent::Release(void) {
    super::Release();
    _hp_com.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerDamageComponent::Clone(void) {
    return std::make_shared<rachet::PlayerDamageComponent>(*this);
}

bool rachet::PlayerDamageComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionDamageState);
    return true;
}