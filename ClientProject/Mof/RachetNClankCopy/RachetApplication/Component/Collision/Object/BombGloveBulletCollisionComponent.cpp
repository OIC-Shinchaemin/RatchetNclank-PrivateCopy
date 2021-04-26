#include "BombGloveBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(int priority) :
    super(priority) {
}

my::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(const BombGloveBulletCollisionComponent& obj) :
    super(obj._priority) {
}

my::BombGloveBulletCollisionComponent::~BombGloveBulletCollisionComponent() {
}

std::string my::BombGloveBulletCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kBombGloveBulletCollisionComponent;
    //return "BombGloveBulletCollisionComponent";
}

std::optional<Mof::CSphere> my::BombGloveBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> my::BombGloveBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::BombGloveBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::BombGloveBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::BombGloveBulletCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::BombGloveBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::BombGloveBulletCollisionComponent::Clone(void) {
    return std::make_shared<my::BombGloveBulletCollisionComponent>(*this);
}

void my::BombGloveBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const Mof::CMatrix44& world) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        super::GetOwner()->End();
    } // if
}