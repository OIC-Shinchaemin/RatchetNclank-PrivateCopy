#include "EnemyBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(int priority) :
    super(priority) {
}

my::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(const EnemyBulletCollisionComponent& obj) :
    super(obj._priority) {
}

my::EnemyBulletCollisionComponent::~EnemyBulletCollisionComponent() {
}

std::string my::EnemyBulletCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kEnemyBulletCollisionComponent;
}

std::optional<Mof::CSphere> my::EnemyBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    return Mof::CSphere(super::GetOwner()->GetPosition(), 0.2f);
}

std::optional<Mof::CBoxAABB> my::EnemyBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemyBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::EnemyBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemyBulletCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::EnemyBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::EnemyBulletCollisionComponent::Clone(void) {
    return std::make_shared<my::EnemyBulletCollisionComponent>(*this);
}

void my::EnemyBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh) {
}