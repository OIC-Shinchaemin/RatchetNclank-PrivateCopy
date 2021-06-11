#include "BoltCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/BoltActionStateComponent.h"


ratchet::BoltCollisionComponent::BoltCollisionComponent(int priority) :
    super(priority),
    _height(0.2f),
    _volume(_height),
    _state_com(){
}

ratchet::BoltCollisionComponent::BoltCollisionComponent(const BoltCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

ratchet::BoltCollisionComponent::~BoltCollisionComponent() {
}

std::string ratchet::BoltCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kBoltCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::BoltCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::BoltCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::BoltCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> ratchet::BoltCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::BoltCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::BoltCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::BoltCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<ratchet::BoltActionStateComponent>();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BoltCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::BoltCollisionComponent>(*this);
}

void ratchet::BoltCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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
                
                //if (_state_com.lock()->CanTransition(state::BoltActionType::kDefault)) {
                    _state_com.lock()->ChangeState(state::BoltActionType::kDefault);
                //} // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}