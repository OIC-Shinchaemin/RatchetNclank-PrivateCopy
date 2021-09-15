#include "ShipCollisionComponent.h"

#include "../CollisionComponentDefine.h"
#include "../../../Component/Ship/ShipStateComponent.h"


ratchet::component::collision::ShipCollisionComponent::ShipCollisionComponent(int priority) :
    super(priority),
    _state_com(),
    _height(3.0f) {
}

ratchet::component::collision::ShipCollisionComponent::ShipCollisionComponent(const ShipCollisionComponent& obj) :
    super(obj),
    _state_com(),
    _height(obj._height) {
}

ratchet::component::collision::ShipCollisionComponent::~ShipCollisionComponent() {
}

std::string ratchet::component::collision::ShipCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kShipCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::ShipCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 2.0f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::ShipCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::ShipCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::ShipCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::ShipCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::ShipCollisionComponent::Initialize(void) {
    super::Initialize();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::ship::ShipStateComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::ShipCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::ShipCollisionComponent>(*this);
}

void ratchet::component::collision::ShipCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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
                    if (state_com->CanTransition(state::ShipActionStateType::kShipActionIdleState)) {
                        state_com->ChangeState(state::ShipActionStateType::kShipActionIdleState);
                    } // if
                } // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}