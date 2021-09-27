#include "BarrackCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::BarrackCollisionComponent::BarrackCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::BarrackCollisionComponent::BarrackCollisionComponent(const BarrackCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::BarrackCollisionComponent::~BarrackCollisionComponent() {
}

std::string ratchet::component::collision::BarrackCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBarrackCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::BarrackCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 2.0f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BarrackCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BarrackCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BarrackCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BarrackCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BarrackCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BarrackCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::BarrackCollisionComponent>(*this);
}

void ratchet::component::collision::BarrackCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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
                    if (state_com->CanTransition(state::BarrackActionStateType::kBarrackActionIdleState)) {
                        state_com->ChangeState(state::BarrackActionStateType::kBarrackActionIdleState);
                    } // if
                } // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
    */
}