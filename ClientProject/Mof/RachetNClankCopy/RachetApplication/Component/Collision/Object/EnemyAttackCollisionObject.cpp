#include "EnemyAttackCollisionObject.h"

#include "../../Enemy/EnemyAttackComponent.h"


my::EnemyAttackCollisionObject::EnemyAttackCollisionObject(int priority) :
    super(priority),
    _attack_com() {
}

my::EnemyAttackCollisionObject::EnemyAttackCollisionObject(const EnemyAttackCollisionObject& obj) :
    super(obj._priority),
    _attack_com() {
}

my::EnemyAttackCollisionObject::~EnemyAttackCollisionObject() {
}

std::string my::EnemyAttackCollisionObject::GetType(void) const {
    return "EnemyAttackCollisionObject";
}

std::optional<Mof::CSphere> my::EnemyAttackCollisionObject::GetSphere(void) {
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

std::optional<Mof::CBoxAABB> my::EnemyAttackCollisionObject::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemyAttackCollisionObject::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::EnemyAttackCollisionObject::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemyAttackCollisionObject::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::EnemyAttackCollisionObject::Initialize(void) {
    super::Initialize();
    _attack_com = super::GetOwner()->GetComponent<my::EnemyAttackComponent>();
    return true;
}

std::shared_ptr<my::Component> my::EnemyAttackCollisionObject::Clone(void) {
    return std::make_shared<my::EnemyAttackCollisionObject>(*this);
}