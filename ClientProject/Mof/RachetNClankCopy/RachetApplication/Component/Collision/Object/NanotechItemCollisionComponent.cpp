#include "NanotechItemCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/NanotechItem/NanotechItemActionStateComponent.h"


my::NanotechItemCollisionComponent::NanotechItemCollisionComponent(int priority) :
    super(priority),
    _height(0.4f),
    _volume(_height),
    _state_com(){
}

my::NanotechItemCollisionComponent::NanotechItemCollisionComponent(const NanotechItemCollisionComponent& obj) :
    super(obj),
    _height(obj._height),
    _volume(obj._volume),
    _state_com() {
}

my::NanotechItemCollisionComponent::~NanotechItemCollisionComponent() {
}

std::string my::NanotechItemCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kNanotechItemCollisionComponent;
}

std::optional<Mof::CSphere> my::NanotechItemCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> my::NanotechItemCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::NanotechItemCollisionComponent::GetRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::CRay3D> my::NanotechItemCollisionComponent::GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::NanotechItemCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::NanotechItemCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::NanotechItemCollisionComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::NanotechItemActionStateComponent>();
    return true;
}

std::shared_ptr<my::Component> my::NanotechItemCollisionComponent::Clone(void) {
    return std::make_shared<my::NanotechItemCollisionComponent>(*this);
}

void my::NanotechItemCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
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