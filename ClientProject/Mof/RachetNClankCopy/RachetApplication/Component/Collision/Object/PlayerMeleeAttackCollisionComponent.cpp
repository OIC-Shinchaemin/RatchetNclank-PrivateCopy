#include "PlayerMeleeAttackCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../Player/PlayerComponent.h"
#include "../../Player/PlayerMeleeAttackOneComponent.h"
#include "../../Player/PlayerMeleeAttackTwoComponent.h"
#include "../../Player/PlayerMeleeAttackThreeComponent.h"


my::PlayerMeleeAttackCollisionComponent::PlayerMeleeAttackCollisionComponent(int priority) :
    super(priority),
    _volume(1.0f),
    _front_offset(1.0f),
    _player_com(),
    _attack_one_com(),
    _attack_two_com(),
    _attack_three_com() {
}

my::PlayerMeleeAttackCollisionComponent::PlayerMeleeAttackCollisionComponent(const PlayerMeleeAttackCollisionComponent& obj) :
    super(obj._priority),
    _volume(obj._volume),
    _front_offset(obj._front_offset),
    _player_com(),
    _attack_one_com(),
    _attack_two_com(),
    _attack_three_com() {
}

my::PlayerMeleeAttackCollisionComponent::~PlayerMeleeAttackCollisionComponent() {
}

std::string my::PlayerMeleeAttackCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kPlayerMeleeAttackCollisionComponent;
}

std::optional<Mof::CSphere> my::PlayerMeleeAttackCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto attack_one_com = _attack_one_com.lock();
    auto attack_two_com = _attack_two_com.lock();
    auto attack_three_com = _attack_three_com.lock();
    if (!attack_one_com->IsActive() && !attack_two_com->IsActive()&& !attack_three_com->IsActive()) {
        return std::optional<Mof::CSphere>();
    } // if

    auto pos = super::GetOwner()->GetPosition();
    auto rotate = super::GetOwner()->GetRotate();

    auto front = Mof::CVector3(-math::vec3::kUnitZ * _front_offset);
    front.RotationY(rotate.y);

    pos += front;    
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> my::PlayerMeleeAttackCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::PlayerMeleeAttackCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::PlayerMeleeAttackCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::PlayerMeleeAttackCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::PlayerMeleeAttackCollisionComponent::Initialize(void) {
    super::Initialize();
    _player_com = super::GetOwner()->GetComponent<my::PlayerComponent>();
    _attack_one_com = super::GetOwner()->GetComponent<my::PlayerMeleeAttackOneComponent>();
    _attack_two_com = super::GetOwner()->GetComponent<my::PlayerMeleeAttackTwoComponent>();
    _attack_three_com = super::GetOwner()->GetComponent<my::PlayerMeleeAttackThreeComponent>();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackCollisionComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackCollisionComponent>(*this);
}