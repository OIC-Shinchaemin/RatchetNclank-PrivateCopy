#include "BarricadeCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::BarricadeCollisionComponent::BarricadeCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::BarricadeCollisionComponent::BarricadeCollisionComponent(const BarricadeCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::BarricadeCollisionComponent::~BarricadeCollisionComponent() {
}

std::string ratchet::component::collision::BarricadeCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBarricadeCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::BarricadeCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 2.0f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BarricadeCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BarricadeCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BarricadeCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BarricadeCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BarricadeCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BarricadeCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::BarricadeCollisionComponent>(*this);
}

void ratchet::component::collision::BarricadeCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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
                    if (state_com->CanTransition(state::BarricadeActionStateType::kBarricadeActionIdleState)) {
                        state_com->ChangeState(state::BarricadeActionStateType::kBarricadeActionIdleState);
                    } // if
                } // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
    */
}