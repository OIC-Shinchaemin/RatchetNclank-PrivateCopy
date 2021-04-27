#include "EnemyCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../Enemy/EnemyComponent.h"


my::EnemyCollisionComponent::EnemyCollisionComponent(int priority) :
    super(priority),
    _enemy_com() {
}

my::EnemyCollisionComponent::EnemyCollisionComponent(const EnemyCollisionComponent& obj) :
    super(obj._priority),
    _enemy_com() {
}

my::EnemyCollisionComponent::~EnemyCollisionComponent() {
}

std::string my::EnemyCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent;
}

std::optional<Mof::CSphere> my::EnemyCollisionComponent::GetSphere(void) {
    _ASSERT_EXPR(!_enemy_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _enemy_com.lock()->GetHeight();
    return Mof::CSphere(pos, _enemy_com.lock()->GetVolume());
}

std::optional<Mof::CBoxAABB> my::EnemyCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemyCollisionComponent::GetRay(void) {
    _ASSERT_EXPR(!_enemy_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _enemy_com.lock()->GetHeight();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> my::EnemyCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemyCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::EnemyCollisionComponent::Initialize(void) {
    super::Initialize();
    _enemy_com = super::GetOwner()->GetComponent<my::EnemyComponent>();
    return true;
}

std::shared_ptr<my::Component> my::EnemyCollisionComponent::Clone(void) {
    return std::make_shared<my::EnemyCollisionComponent>(*this);
}

void my::EnemyCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        Mof::CVector3 scale; mat.GetScaling(scale);
        Mof::CVector3 trans; mat.GetTranslation(trans);

        Mof::CBoxAABB box; geometry->CalculateAABB(box);
        box.Size.x *= scale.x; box.Size.y *= scale.y; box.Size.z *= scale.z;
        box.Position.x += trans.x; box.Position.y += trans.y; box.Position.z += trans.z;
        std::swap(box.Size.y, box.Size.z);

        auto pos = super::GetOwner()->GetPosition();
        pos.y -= _enemy_com.lock()->GetHeight();
        box.Position.y += _enemy_com.lock()->GetHeight();
        if (!super::CollisionShpereAABB(this->GetSphere().value(), box)) {
            geometry->SetMatrix(default_matrix);
            continue;
        } // if




        if (ray.CollisionGeometry(geometry, info)) {
            float height = _enemy_com.lock()->GetHeight();
            if (info.d <= height) {
                auto pos = super::GetOwner()->GetPosition();
                pos.y += height - info.d;
                super::GetOwner()->SetPosition(pos);
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}