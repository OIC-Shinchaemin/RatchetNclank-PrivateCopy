#include "ScarecrowCollisionComponent.h"

#include "../CollisionComponentDefine.h"

#include "../../Scarecrow/ScarecrowComponent.h"
#include "../../VelocityComponent.h"


ratchet::component::collision::ScarecrowCollisionComponent::ScarecrowCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::ScarecrowCollisionComponent::ScarecrowCollisionComponent(const ScarecrowCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::ScarecrowCollisionComponent::~ScarecrowCollisionComponent() {
}

std::string ratchet::component::collision::ScarecrowCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::ScarecrowCollisionComponent::GetSphere(void) {
    _ASSERT_EXPR(!_type_com.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _type_com.lock()->GetHeight();
    return Mof::CSphere(pos, _type_com.lock()->GetVolume());
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::ScarecrowCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::ScarecrowCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::ScarecrowCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::ScarecrowCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::ScarecrowCollisionComponent::Initialize(void) {
    super::Initialize();
    _type_com = super::GetOwner()->GetComponent<ratchet::component::scarecrow::ScarecrowComponent>();
    //_state_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::ScarecrowCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::ScarecrowCollisionComponent>(*this);
}

void ratchet::component::collision::ScarecrowCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}