#include "BlasterBulletCollisionObject.h"


my::BlasterBulletCollisionObject::BlasterBulletCollisionObject(int priority) :
    super(priority) {
}

my::BlasterBulletCollisionObject::BlasterBulletCollisionObject(const BlasterBulletCollisionObject& obj) :
    super(obj._priority) {
}

my::BlasterBulletCollisionObject::~BlasterBulletCollisionObject() {
}

std::string my::BlasterBulletCollisionObject::GetType(void) const {
    return "BlasterBulletCollisionObject";
}

std::optional<Mof::CSphere> my::BlasterBulletCollisionObject::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> my::BlasterBulletCollisionObject::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::BlasterBulletCollisionObject::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::BlasterBulletCollisionObject::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::BlasterBulletCollisionObject::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::BlasterBulletCollisionObject::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::BlasterBulletCollisionObject::Clone(void) {
    return std::make_shared<my::BlasterBulletCollisionObject>(*this);
}

void my::BlasterBulletCollisionObject::CollisionStage(Mof::LPMeshContainer mesh) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        //Start();
    } // if
}