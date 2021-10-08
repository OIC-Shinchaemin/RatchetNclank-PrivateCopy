#include "CameraCollisionComponent.h"

#include "../CollisionComponentDefine.h"
#include "../../CameraComponent.h"


ratchet::component::collision::CameraCollisionComponent::CameraCollisionComponent(int priority) :
    super(priority),
    _camera_com() {
}

ratchet::component::collision::CameraCollisionComponent::CameraCollisionComponent(const CameraCollisionComponent& obj) :
    super(obj),
    _camera_com() {
}

ratchet::component::collision::CameraCollisionComponent ::~CameraCollisionComponent() {
}

std::string ratchet::component::collision::CameraCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kCameraCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::CameraCollisionComponent::GetSphere(void) {
    _ASSERT_EXPR(!_camera_com.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = _camera_com.lock()->GetPosition();
    return Mof::CSphere(pos, 0.5f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::CameraCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::CameraCollisionComponent::GetRay(void) {
    _ASSERT_EXPR(!_camera_com.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = _camera_com.lock()->GetPosition();
    //auto velocity = _camera_com.lock()->GetVelocity();
    auto target = _camera_com.lock()->GetCameraController()->GetService()->GetCamera()->GetTarget();
    return Mof::CRay3D(pos, pos - target);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::CameraCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::CameraCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::CameraCollisionComponent::Initialize(void) {
    super::Initialize();
    _camera_com = super::GetOwner()->GetComponent<ratchet::component::CameraComponent>();

    _non_collision_angle.y = 30.0f;
    _non_collision_angle.x = 0.0f;
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::CameraCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::CameraCollisionComponent>(*this);
}

void ratchet::component::collision::CameraCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    auto camera_com = _camera_com.lock();
    auto controller = camera_com->GetCameraController()->GetService();
    auto pos = _camera_com.lock()->GetPosition();
    auto sphere = this->GetSphere().value();
    auto ray = this->GetRay().value();

    Mof::COLLISIONOUTGEOMETRY info;
    float margin = 0.0f;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        auto camera_info = camera::CameraController::CameraInfo();
        camera_info.target_position = controller->GetCamera()->GetTarget();
        //if (sphere.CollisionGeometry(geometry, info)) {
        if (ray.CollisionGeometry(geometry, info)) {
            if (info.d <= sphere.r + margin) {
                // �����߂Â�
                float distance = info.d;
                distance = std::clamp(distance, sphere.r, controller->GetDefaultDistance() );
                controller->SetDistance(distance);
                controller->Update(def::kDeltaTime, camera_info);
                this->CollisionStage(mesh, obj);
            } // if
            else {
                float distance = info.d;
                distance = std::clamp(distance, sphere.r, controller->GetDefaultDistance());
                controller->SetDistance(distance);
//                controller->SetDistance(controller->GetDefaultDistance());
  //              controller->Update(def::kDeltaTime, camera_info);
            } // else
        } // if
        else {
            _non_collision_distance = controller->GetDistance();
        } // else
        geometry->SetMatrix(default_matrix);
    } // for
}

void ratchet::component::collision::CameraCollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
}