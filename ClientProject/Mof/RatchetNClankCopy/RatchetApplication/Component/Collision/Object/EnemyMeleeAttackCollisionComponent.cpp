#include "EnemyMeleeAttackCollisionComponent.h"

#include "../CollisionComponentDefine.h"
#include "../../Enemy/EnemyMeleeAttackComponent.h"


ratchet::component::collision::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(int priority) :
    super(priority),
    _attack_com() {
}

ratchet::component::collision::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(const EnemyMeleeAttackCollisionComponent& obj) :
    super(obj),
    _attack_com() {
}

ratchet::component::collision::EnemyMeleeAttackCollisionComponent::~EnemyMeleeAttackCollisionComponent() {
}

std::string ratchet::component::collision::EnemyMeleeAttackCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyMeleeAttackCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::EnemyMeleeAttackCollisionComponent::GetSphere(void) {
    if (_attack_com.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
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

std::optional<Mof::CBoxAABB> ratchet::component::collision::EnemyMeleeAttackCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::EnemyMeleeAttackCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::EnemyMeleeAttackCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::EnemyMeleeAttackCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::EnemyMeleeAttackCollisionComponent::Initialize(void) {
    super::Initialize();
    this->Inactivate();
    _attack_com = super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::enemy::EnemyMeleeAttackComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::EnemyMeleeAttackCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::EnemyMeleeAttackCollisionComponent>(*this);
}