#include "CameraCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../CameraComponent.h"


rachet::CameraCollisionComponent::CameraCollisionComponent(int priority) :
    super(priority),
    _camera_com() {
}

rachet::CameraCollisionComponent::CameraCollisionComponent(const CameraCollisionComponent& obj) :
    super(obj),
    _camera_com() {
}

rachet::CameraCollisionComponent ::~CameraCollisionComponent() {
}

std::string rachet::CameraCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kCameraCollisionComponent;
}

std::optional<Mof::CSphere> rachet::CameraCollisionComponent::GetSphere(void) {
    return std::optional<Mof::CSphere>();
}

std::optional<Mof::CBoxAABB> rachet::CameraCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::CameraCollisionComponent::GetRay(void) {
    _ASSERT_EXPR(!_camera_com.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = _camera_com.lock()->GetPosition();
    auto velocity = _camera_com.lock()->GetVelocity();
    return Mof::CRay3D(pos, velocity);
}

std::optional<Mof::LPMeshContainer> rachet::CameraCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::CameraCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::CameraCollisionComponent::Initialize(void) {
    super::Initialize();
    _camera_com = super::GetOwner()->GetComponent<rachet::CameraComponent>();
    return true;
}

std::shared_ptr<rachet::Component> rachet::CameraCollisionComponent::Clone(void) {
    return std::make_shared<rachet::CameraCollisionComponent>(*this);
}

void rachet::CameraCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    auto camera_com = _camera_com.lock();
    auto pos = _camera_com.lock()->GetPosition();
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;
    float matgin = 0.1f;
    float volume = 2.0f;
    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        if (ray.CollisionGeometry(geometry, info)) {
            if (info.d <= volume) {
                camera_com->CollisionStage();
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}

void rachet::CameraCollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
}