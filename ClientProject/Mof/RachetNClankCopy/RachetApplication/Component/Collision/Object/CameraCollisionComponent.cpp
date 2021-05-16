#include "CameraCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../CameraComponent.h"


my::CameraCollisionComponent::CameraCollisionComponent(int priority) :
    super(priority),
    _camera_com() {
}

my::CameraCollisionComponent::CameraCollisionComponent(const CameraCollisionComponent& obj) :
    super(obj),
    _camera_com() {
}

my::CameraCollisionComponent ::~CameraCollisionComponent() {
}

std::string my::CameraCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kCameraCollisionComponent;
}

std::optional<Mof::CSphere> my::CameraCollisionComponent::GetSphere(void) {
    return std::optional<Mof::CSphere>();
}

std::optional<Mof::CBoxAABB> my::CameraCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::CameraCollisionComponent::GetRay(void) {
    _ASSERT_EXPR(!_camera_com.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = _camera_com.lock()->GetPosition();
    auto velocity = _camera_com.lock()->GetVelocity();
    return Mof::CRay3D(pos, velocity);
}

std::optional<Mof::LPMeshContainer> my::CameraCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::CameraCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::CameraCollisionComponent::Initialize(void) {
    super::Initialize();
    _camera_com = super::GetOwner()->GetComponent<my::CameraComponent>();
    return true;
}

std::shared_ptr<my::Component> my::CameraCollisionComponent::Clone(void) {
    return std::make_shared<my::CameraCollisionComponent>(*this);
}

void my::CameraCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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

void my::CameraCollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
}