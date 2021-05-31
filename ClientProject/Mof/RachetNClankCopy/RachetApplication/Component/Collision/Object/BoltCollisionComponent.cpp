#include "BoltCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/BoltActionStateComponent.h"


my::BoltCollisionComponent::BoltCollisionComponent(int priority) :
    super(priority),
    _height(0.2f),
    _volume(_height),
    _state_com(){
}

my::BoltCollisionComponent::BoltCollisionComponent(const BoltCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

my::BoltCollisionComponent::~BoltCollisionComponent() {
}

std::string my::BoltCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kBoltCollisionComponent;
}

std::optional<Mof::CSphere> my::BoltCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> my::BoltCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::BoltCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> my::BoltCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::BoltCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::BoltCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::BoltCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::BoltActionStateComponent>();
    return true;
}

std::shared_ptr<my::Component> my::BoltCollisionComponent::Clone(void) {
    return std::make_shared<my::BoltCollisionComponent>(*this);
}

void my::BoltCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if
    if (_state_com.lock()->IsEqual(state::BoltActionType::kGravitate)) {
        return;
    } // if


    auto sphere = this->GetSphere().value();
    Mof::COLLISIONOUTGEOMETRY info;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        if (sphere.CollisionGeometry(geometry, info)) {
            if (info.d <= _height) {
                auto pos = super::GetOwner()->GetPosition();
                pos.y += _height - info.d;
                super::GetOwner()->SetPosition(pos);

                
                if (_state_com.lock()->CanTransition(state::BoltActionType::kDefault)) {
                    _state_com.lock()->ChangeState(state::BoltActionType::kDefault);
                } // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}