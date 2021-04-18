#include "EnemyCollisionObject.h"

#include "../../Enemy/EnemyComponent.h"


my::EnemyCollisionObject::EnemyCollisionObject(int priority) :
    super(priority),
    _enemy_com() {
}

my::EnemyCollisionObject::EnemyCollisionObject(const EnemyCollisionObject& obj) :
    super(obj._priority),
    _enemy_com() {
}

my::EnemyCollisionObject::~EnemyCollisionObject() {
}

std::string my::EnemyCollisionObject::GetType(void) const {
    return "EnemyCollisionObject";
}

std::optional<Mof::CSphere> my::EnemyCollisionObject::GetSphere(void) {    
    _ASSERT_EXPR(!_enemy_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _enemy_com.lock()->GetHeight();
    return Mof::CSphere(pos, _enemy_com.lock()->GetVolume());
}

std::optional<Mof::CBoxAABB> my::EnemyCollisionObject::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemyCollisionObject::GetRay(void) {
    _ASSERT_EXPR(!_enemy_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _enemy_com.lock()->GetHeight();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> my::EnemyCollisionObject::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemyCollisionObject::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::EnemyCollisionObject::Initialize(void) {
    super::Initialize();
    _enemy_com = super::GetOwner()->GetComponent<my::EnemyComponent>();

    return true;
}

std::shared_ptr<my::Component> my::EnemyCollisionObject::Clone(void) {
    return std::make_shared<my::EnemyCollisionObject>(*this);
}

void my::EnemyCollisionObject::CollisionStage(Mof::LPMeshContainer mesh) {
    if (!this->GetRay().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetRay().value().CollisionMesh(mesh, info)) {
        float height = _enemy_com.lock()->GetHeight();
        if (info.d <= height) {
            auto pos = super::GetOwner()->GetPosition();
            pos.y += height - info.d;
            super::GetOwner()->SetPosition(pos);
        } // if
    } // if
}