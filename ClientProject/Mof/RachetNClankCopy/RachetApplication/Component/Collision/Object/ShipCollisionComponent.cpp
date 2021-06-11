#include "ShipCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../../Component/Ship/ShipStateComponent.h"


rachet::ShipCollisionComponent::ShipCollisionComponent(int priority) :
    super(priority),
    _state_com(),
    _height(3.0f) {
}

rachet::ShipCollisionComponent::ShipCollisionComponent(const ShipCollisionComponent& obj) :
    super(obj),
    _state_com(),
    _height(obj._height) {
}

rachet::ShipCollisionComponent::~ShipCollisionComponent() {
}

std::string rachet::ShipCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kShipCollisionComponent;
}

std::optional<Mof::CSphere> rachet::ShipCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 2.0f);
}

std::optional<Mof::CBoxAABB> rachet::ShipCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::ShipCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> rachet::ShipCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::ShipCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::ShipCollisionComponent::Initialize(void) {
    super::Initialize();
    _state_com = super::GetOwner()->GetComponent<rachet::ShipStateComponent>();
    return true;
}

std::shared_ptr<rachet::Component> rachet::ShipCollisionComponent::Clone(void) {
    return std::make_shared<rachet::ShipCollisionComponent>(*this);
}

void rachet::ShipCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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