#include "BulletItemCollisionComponent.h"

#include "../CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/BulletItem/BulletItemActionStateComponent.h"


ratchet::component::collision::BulletItemCollisionComponent::BulletItemCollisionComponent(int priority) :
    super(priority),
    _height(0.6f),
    _volume(_height),
    _state_com(){
}

ratchet::component::collision::BulletItemCollisionComponent::BulletItemCollisionComponent(const BulletItemCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

ratchet::component::collision::BulletItemCollisionComponent::~BulletItemCollisionComponent() {
}

std::string ratchet::component::collision::BulletItemCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBulletItemCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::BulletItemCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BulletItemCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BulletItemCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BulletItemCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BulletItemCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BulletItemCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BulletItemCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::bulletitem::BulletItemActionStateComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BulletItemCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::BulletItemCollisionComponent>(*this);
}

void ratchet::component::collision::BulletItemCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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