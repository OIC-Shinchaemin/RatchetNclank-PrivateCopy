#include "NanotechItemCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/NanotechItem/NanotechItemActionStateComponent.h"


rachet::NanotechItemCollisionComponent::NanotechItemCollisionComponent(int priority) :
    super(priority),
    _height(0.4f),
    _volume(_height),
    _state_com(){
}

rachet::NanotechItemCollisionComponent::NanotechItemCollisionComponent(const NanotechItemCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

rachet::NanotechItemCollisionComponent::~NanotechItemCollisionComponent() {
}

std::string rachet::NanotechItemCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kNanotechItemCollisionComponent;
}

std::optional<Mof::CSphere> rachet::NanotechItemCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> rachet::NanotechItemCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::NanotechItemCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> rachet::NanotechItemCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::NanotechItemCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::NanotechItemCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::NanotechItemCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<rachet::NanotechItemActionStateComponent>();
    return true;
}

std::shared_ptr<rachet::Component> rachet::NanotechItemCollisionComponent::Clone(void) {
    return std::make_shared<rachet::NanotechItemCollisionComponent>(*this);
}

void rachet::NanotechItemCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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