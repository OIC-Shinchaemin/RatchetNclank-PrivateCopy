#include "EnemyMeleeAttackCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../Enemy/EnemyMeleeAttackComponent.h"


rachet::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(int priority) :
    super(priority),
    _attack_com() {
}

rachet::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(const EnemyMeleeAttackCollisionComponent& obj) :
    super(obj),
    _attack_com() {
}

rachet::EnemyMeleeAttackCollisionComponent::~EnemyMeleeAttackCollisionComponent() {
}

std::string rachet::EnemyMeleeAttackCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kEnemyMeleeAttackCollisionComponent;
}

std::optional<Mof::CSphere> rachet::EnemyMeleeAttackCollisionComponent::GetSphere(void) {
    if (_attack_com.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
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

std::optional<Mof::CBoxAABB> rachet::EnemyMeleeAttackCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::EnemyMeleeAttackCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::EnemyMeleeAttackCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::EnemyMeleeAttackCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::EnemyMeleeAttackCollisionComponent::Initialize(void) {
    super::Initialize();
    this->Inactivate();
    _attack_com = super::GetOwner()->GetComponent<rachet::ActionComponent>()->GetComponent<rachet::EnemyMeleeAttackComponent>();
    return true;
}

std::shared_ptr<rachet::Component> rachet::EnemyMeleeAttackCollisionComponent::Clone(void) {
    return std::make_shared<rachet::EnemyMeleeAttackCollisionComponent>(*this);
}