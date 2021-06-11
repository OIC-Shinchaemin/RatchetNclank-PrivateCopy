#include "BombGloveBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(int priority) :
    super(priority) {
}

rachet::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(const BombGloveBulletCollisionComponent& obj) :
    super(obj) {
}

rachet::BombGloveBulletCollisionComponent::~BombGloveBulletCollisionComponent() {
}

std::string rachet::BombGloveBulletCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kBombGloveBulletCollisionComponent;
    //return "BombGloveBulletCollisionComponent";
}

std::optional<Mof::CSphere> rachet::BombGloveBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> rachet::BombGloveBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::BombGloveBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::BombGloveBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::BombGloveBulletCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::BombGloveBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BombGloveBulletCollisionComponent::Clone(void) {
    return std::make_shared<rachet::BombGloveBulletCollisionComponent>(*this);
}

void rachet::BombGloveBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        super::GetOwner()->End();
    } // if
}