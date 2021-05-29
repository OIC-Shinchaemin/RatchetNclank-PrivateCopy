#include "EnemyMeleeAttackCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../Enemy/EnemyMeleeAttackComponent.h"


my::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(int priority) :
    super(priority),
    _attack_com() {
}

my::EnemyMeleeAttackCollisionComponent::EnemyMeleeAttackCollisionComponent(const EnemyMeleeAttackCollisionComponent& obj) :
    super(obj),
    _attack_com() {
}

my::EnemyMeleeAttackCollisionComponent::~EnemyMeleeAttackCollisionComponent() {
}

std::string my::EnemyMeleeAttackCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kEnemyMeleeAttackCollisionComponent;
}

std::optional<Mof::CSphere> my::EnemyMeleeAttackCollisionComponent::GetSphere(void) {
    if (_attack_com.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner()->GetState() == my::ActorState::End) {
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

std::optional<Mof::CBoxAABB> my::EnemyMeleeAttackCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemyMeleeAttackCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::EnemyMeleeAttackCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemyMeleeAttackCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::EnemyMeleeAttackCollisionComponent::Initialize(void) {
    super::Initialize();
    this->Inactivate();
    _attack_com = super::GetOwner()->GetComponent<my::EnemyMeleeAttackComponent>();
    return true;
}

std::shared_ptr<my::Component> my::EnemyMeleeAttackCollisionComponent::Clone(void) {
    return std::make_shared<my::EnemyMeleeAttackCollisionComponent>(*this);
}