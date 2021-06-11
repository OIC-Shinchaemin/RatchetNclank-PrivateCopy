#include "BulletItemCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/BulletItem/BulletItemActionStateComponent.h"


ratchet::BulletItemCollisionComponent::BulletItemCollisionComponent(int priority) :
    super(priority),
    _height(0.6f),
    _volume(_height),
    _state_com(){
}

ratchet::BulletItemCollisionComponent::BulletItemCollisionComponent(const BulletItemCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

ratchet::BulletItemCollisionComponent::~BulletItemCollisionComponent() {
}

std::string ratchet::BulletItemCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kBulletItemCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::BulletItemCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::BulletItemCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::BulletItemCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> ratchet::BulletItemCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::BulletItemCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::BulletItemCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::BulletItemCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<ratchet::BulletItemActionStateComponent>();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BulletItemCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::BulletItemCollisionComponent>(*this);
}

void ratchet::BulletItemCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if
    if (_state_com.lock()->IsEqual(state::BulletItemActionType::kGravitate)) {
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
                
                //if (_state_com.lock()->CanTransition(state::BulletItemActionType::kDefault)) {
                    _state_com.lock()->ChangeState(state::BulletItemActionType::kDefault);
                //} // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}