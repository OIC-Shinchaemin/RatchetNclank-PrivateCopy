#include "FenceCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::FenceCollisionComponent::FenceCollisionComponent(int priority) :
    super(priority),
    _height(3.0f) {
}

ratchet::component::collision::FenceCollisionComponent::FenceCollisionComponent(const FenceCollisionComponent& obj) :
    super(obj),
    _height(obj._height) {
}

ratchet::component::collision::FenceCollisionComponent::~FenceCollisionComponent() {
}

std::string ratchet::component::collision::FenceCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kFenceCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::FenceCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 2.0f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::FenceCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::FenceCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::FenceCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::FenceCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::FenceCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::FenceCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::FenceCollisionComponent>(*this);
}

void ratchet::component::collision::FenceCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    /*
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;
    float margin = 0.1f;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        if (ray.CollisionGeometry(geometry, info)) {
            if (info.d <= _height + margin) {
                auto pos = super::GetOwner()->GetPosition();
                pos.y += _height + margin - info.d;
                super::GetOwner()->SetPosition(pos);
                if (auto state_com = _state_com.lock()) {
                    if (state_com->CanTransition(state::FenceActionStateType::kFenceActionIdleState)) {
                        state_com->ChangeState(state::FenceActionStateType::kFenceActionIdleState);
                    } // if
                } // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
    */
}