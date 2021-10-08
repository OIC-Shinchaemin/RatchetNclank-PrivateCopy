#include "EnemyCollisionComponent.h"

#include "../CollisionComponentDefine.h"
#include "../../Enemy/EnemyComponent.h"


void ratchet::component::collision::EnemyCollisionComponent::CollisionStageDownRay(Mof::LPMeshContainer mesh, const StageObject& obj) {
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;
    float margin = 0.1f;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        if (ray.CollisionGeometry(geometry, info)) {
            float height = _ENEMY_com.lock()->GetHeight();

            _collision_point_stage_down_ray = super::GetOwner()->GetPosition();
            _collision_point_stage_down_ray.y += height + margin - info.d;

            if (info.d <= height + margin) {
                auto pos = super::GetOwner()->GetPosition();
                pos.y += height + margin - info.d;
                super::GetOwner()->SetPosition(pos);
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}

ratchet::component::collision::EnemyCollisionComponent::EnemyCollisionComponent(int priority) :
    super(priority),
    _ENEMY_com() {
}

ratchet::component::collision::EnemyCollisionComponent::EnemyCollisionComponent(const EnemyCollisionComponent& obj) :
    super(obj),
    _ENEMY_com() {
}

ratchet::component::collision::EnemyCollisionComponent::~EnemyCollisionComponent() {
}

std::string ratchet::component::collision::EnemyCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::EnemyCollisionComponent::GetSphere(void) {
    _ASSERT_EXPR(!_ENEMY_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _ENEMY_com.lock()->GetHeight();
    return Mof::CSphere(pos, _ENEMY_com.lock()->GetVolume());
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::EnemyCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::EnemyCollisionComponent::GetRay(void) {
    _ASSERT_EXPR(!_ENEMY_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _ENEMY_com.lock()->GetHeight();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::EnemyCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::EnemyCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::EnemyCollisionComponent::Initialize(void) {
    super::Initialize();
    _ENEMY_com = super::GetOwner()->GetComponent<ratchet::component::enemy::EnemyComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::EnemyCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::EnemyCollisionComponent>(*this);
}

void ratchet::component::collision::EnemyCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    bool execute = false;
    auto check_sphere = this->GetSphere().value();
    check_sphere.r *= 2.0f;
    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        if (check_sphere.CollisionSphere(obj.GetGeometrySphere(i))) {
            execute = true;
            break;
        } // if
    } // for

    if (!execute) {
        return;
    } // if
    this->CollisionStageDownRay(mesh, obj);
    //_ENEMY_com.lock()->GetOwnerCastd()->GetShadowChildActor()->SetPosition(_collision_point_stage_down_ray);
}