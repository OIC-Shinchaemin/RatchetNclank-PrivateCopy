#include "ShipCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../../Component/Ship/ShipStateComponent.h"


my::ShipCollisionComponent::ShipCollisionComponent(int priority) :
    super(priority),
    _state_com(),
    _height(3.0f) {
}

my::ShipCollisionComponent::ShipCollisionComponent(const ShipCollisionComponent& obj) :
    super(obj),
    _state_com(),
    _height(obj._height) {
}

my::ShipCollisionComponent::~ShipCollisionComponent() {
}

std::string my::ShipCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kShipCollisionComponent;
}

std::optional<Mof::CSphere> my::ShipCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 2.0f);
}

std::optional<Mof::CBoxAABB> my::ShipCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::ShipCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> my::ShipCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::ShipCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::ShipCollisionComponent::Initialize(void) {
    super::Initialize();
    _state_com = super::GetOwner()->GetComponent<my::ShipStateComponent>();
    return true;
}

std::shared_ptr<my::Component> my::ShipCollisionComponent::Clone(void) {
    return std::make_shared<my::ShipCollisionComponent>(*this);
}

void my::ShipCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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