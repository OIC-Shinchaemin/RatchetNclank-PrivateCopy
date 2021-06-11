#include "EnemyMeleeAttackCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../Enemy/EnemyMeleeAttackComponent.h"


ratchet::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(int priority) :
    super(priority),
    _attack_com() {
}

ratchet::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(const EnemyMeleeAttackCollisionComponent& obj) :
    super(obj),
    _attack_com() {
}

ratchet::EnemyMeleeAttackCollisionComponent::~EnemyMeleeAttackCollisionComponent() {
}

std::string ratchet::EnemyMeleeAttackCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kEnemyMeleeAttackCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::EnemyMeleeAttackCollisionComponent::GetSphere(void) {
    if (_attack_com.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner()->GetState() == ratchet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto attack_com = _attack_com.lock();

    auto pos = super::GetOwner()->GetPosition();
    auto rotate = super::GetOwner()->GetRotate();

    float offset = 1.0f;
    auto front = Mof::CVector3(-math::vec3::kUnitZ * offset);
    front.RotationY(rotate.y);

    pos += front;
    pos.y += 1.0f;

    return Mof::CSphere(pos, attack_com->GetVolume());
}

std::optional<Mof::CBoxAABB> ratchet::EnemyMeleeAttackCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::EnemyMeleeAttackCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::EnemyMeleeAttackCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::EnemyMeleeAttackCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::EnemyMeleeAttackCollisionComponent::Initialize(void) {
    super::Initialize();
    this->Inactivate();
    _attack_com = super::GetOwner()->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::EnemyMeleeAttackComponent>();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::EnemyMeleeAttackCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::EnemyMeleeAttackCollisionComponent>(*this);
}