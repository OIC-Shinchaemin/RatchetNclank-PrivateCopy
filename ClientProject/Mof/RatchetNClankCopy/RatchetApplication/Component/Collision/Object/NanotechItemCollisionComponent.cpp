#include "NanotechItemCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/NanotechItem/NanotechItemActionStateComponent.h"


ratchet::component::collision::NanotechItemCollisionComponent::NanotechItemCollisionComponent(int priority) :
    super(priority),
    _height(0.4f),
    _volume(_height),
    _state_com(){
}

ratchet::component::collision::NanotechItemCollisionComponent::NanotechItemCollisionComponent(const NanotechItemCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

ratchet::component::collision::NanotechItemCollisionComponent::~NanotechItemCollisionComponent() {
}

std::string ratchet::component::collision::NanotechItemCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kNanotechItemCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::NanotechItemCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::NanotechItemCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::NanotechItemCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::NanotechItemCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::NanotechItemCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::NanotechItemCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::NanotechItemCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::nanotechitem::NanotechItemActionStateComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::NanotechItemCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::NanotechItemCollisionComponent>(*this);
}

void ratchet::component::collision::NanotechItemCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if
    if (_state_com.lock()->IsEqual(state::NanotechItemActionType::kGravitate)) {
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
                
                //if (_state_com.lock()->CanTransition(state::NanotechItemActionType::kDefault)) {
                    _state_com.lock()->ChangeState(state::NanotechItemActionType::kDefault);
                //} // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}