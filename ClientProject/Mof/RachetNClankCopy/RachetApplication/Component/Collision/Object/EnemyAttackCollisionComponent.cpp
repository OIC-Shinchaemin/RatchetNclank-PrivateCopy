#include "EnemyAttackCollisionComponent.h"

#include "../../Enemy/EnemyAttackComponent.h"


my::EnemyAttackCollisionComponent::EnemyAttackCollisionComponent(int priority) :
    super(priority),
    _attack_com() {
}

my::EnemyAttackCollisionComponent::EnemyAttackCollisionComponent(const EnemyAttackCollisionComponent& obj) :
    super(obj._priority),
    _attack_com() {
}

my::EnemyAttackCollisionComponent::~EnemyAttackCollisionComponent() {
}

std::string my::EnemyAttackCollisionComponent::GetType(void) const {
    return "EnemyAttackCollisionComponent";
}

std::optional<Mof::CSphere> my::EnemyAttackCollisionComponent::GetSphere(void) {
    if (_attack_com.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto attack_com = _attack_com.lock();
    if (!attack_com->IsActive()) {
        return std::optional<Mof::CSphere>();
    } // if
    
    auto pos = super::GetOwner()->GetPosition();
    auto rotate = super::GetOwner()->GetRotate();

    float offset = 1.0f;
    auto front = Mof::CVector3(-math::vec3::kUnitZ * offset);
    front.RotationY(rotate.y);

    pos += front;
    pos.y += 1.0f;

    return Mof::CSphere(pos, attack_com->GetVolume());
}

std::optional<Mof::CBoxAABB> my::EnemyAttackCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemyAttackCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::EnemyAttackCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemyAttackCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::EnemyAttackCollisionComponent::Initialize(void) {
    super::Initialize();
    _attack_com = super::GetOwner()->GetComponent<my::EnemyAttackComponent>();
    return true;
}

std::shared_ptr<my::Component> my::EnemyAttackCollisionComponent::Clone(void) {
    return std::make_shared<my::EnemyAttackCollisionComponent>(*this);
}