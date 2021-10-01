#include "PlayerDamageComponent.h"

#include "../HpComponent.h"
#include "../Collision/CollisionComponentDefine.h"
#include "../Collision/Object/PlayerCollisionComponent.h"
#include "PlayerComponent.h"
#include "../../Actor/Character/Player.h"


void ratchet::component::player::action::PlayerDamageComponent::DamegeAccele(void) {
    auto velocity_com = super::GetVelocityComponent();
    auto accele = Mof::CVector3(0.0f, 0.0f, -_damage_speed);
    accele.RotateAround(math::vec3::kZero, _damage_angle);
    velocity_com->SetVelocity(math::vec3::kZero);
    velocity_com->AddVelocityForce(accele);
}

void ratchet::component::player::action::PlayerDamageComponent::Damege(void) {
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

void ratchet::component::player::action::PlayerDamageComponent::Heal(void) {
    if (auto hp_com = _hp_com.lock()) {
        hp_com->Heal(1);
    } // if
}

ratchet::component::player::action::PlayerDamageComponent::PlayerDamageComponent(int priority) :
    super(priority),
    _damage_value(),
    _damage_speed(),
    _damage_angle(),
    _hp_com() {
}

ratchet::component::player::action::PlayerDamageComponent::PlayerDamageComponent(const PlayerDamageComponent& obj) :
    super(obj),
    _damage_value(),
    _damage_speed(),
    _damage_angle(),
    _hp_com() {
}

ratchet::component::player::action::PlayerDamageComponent::~PlayerDamageComponent() {
}

std::string ratchet::component::player::action::PlayerDamageComponent::GetType(void) const {
    return "PlayerDamageComponent";
}

std::string_view ratchet::component::player::action::PlayerDamageComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDamageState;
}

bool ratchet::component::player::action::PlayerDamageComponent::Initialize(void) {
    super::Initialize();
    _hp_com = super::GetOwner()->GetComponent<ratchet::component::HpComponent>();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kEnemyMeleeAttackCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        if (super::CanTransitionActionState(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_speed = in.speed;
            this->_damage_angle = in.angle;
            this->DamegeAccele();
            this->Damege();
            
            auto type_com = super::GetOwner()->GetComponent<player::PlayerComponent>();
            auto message = actor::character::CharacterDamageApplyMessageFactory().Create(super::GetOwner());
            type_com->GetOwnerCastd()->GetCharacterDamageApplyMessageSubject()->Notify(message);
            //std::dynamic_pointer_cast<ratchet::actor::character::> (super::GetOwner())->GetCharacterDamageApplyMessageSubject()->Notify(message);
        } // if
        return true;
    }));

    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kNanotechItemCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        this->Heal();
        return true;
    }));


    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kEnemyBulletCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        if (super::CanTransitionActionState(state::PlayerActionStateType::kPlayerActionDamageState)) {
            this->_damage_value = 1;
            this->_damage_speed = in.speed;
            this->_damage_angle = in.angle;
            this->DamegeAccele();
            this->Damege();
            //super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDamageState);
            auto type_com = super::GetOwner()->GetComponent<player::PlayerComponent>();
            auto message = actor::character::CharacterDamageApplyMessageFactory().Create(super::GetOwner());
            type_com->GetOwnerCastd()->GetCharacterDamageApplyMessageSubject()->Notify(message);

        } // if
        return true;
    }));
    return true;
}

bool ratchet::component::player::action::PlayerDamageComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerDamageComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerDamageComponent::Release(void) {
    super::Release();
    _hp_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerDamageComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerDamageComponent>(*this);
}

bool ratchet::component::player::action::PlayerDamageComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionDamageState);
    return true;
}