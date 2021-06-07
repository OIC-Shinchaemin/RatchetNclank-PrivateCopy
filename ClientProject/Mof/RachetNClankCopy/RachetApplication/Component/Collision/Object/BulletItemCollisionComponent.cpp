#include "BulletItemCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/BulletItem/BulletItemActionStateComponent.h"


my::BulletItemCollisionComponent::BulletItemCollisionComponent(int priority) :
    super(priority),
    _height(0.2f),
    _volume(_height),
    _state_com(){
}

my::BulletItemCollisionComponent::BulletItemCollisionComponent(const BulletItemCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

my::BulletItemCollisionComponent::~BulletItemCollisionComponent() {
}

std::string my::BulletItemCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kBulletItemCollisionComponent;
}

std::optional<Mof::CSphere> my::BulletItemCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> my::BulletItemCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::BulletItemCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> my::BulletItemCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::BulletItemCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::BulletItemCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::BulletItemCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::BulletItemActionStateComponent>();
    return true;
}

std::shared_ptr<my::Component> my::BulletItemCollisionComponent::Clone(void) {
    return std::make_shared<my::BulletItemCollisionComponent>(*this);
}

void my::BulletItemCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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