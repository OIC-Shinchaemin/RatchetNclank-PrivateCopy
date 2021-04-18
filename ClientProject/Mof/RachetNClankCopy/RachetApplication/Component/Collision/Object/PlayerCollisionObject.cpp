#include "PlayerCollisionObject.h"

#include "../../Player/PlayerComponent.h"


my::PlayerCollisionObject::PlayerCollisionObject(int priority) :
    super(priority),
    _player_com() {
}

my::PlayerCollisionObject::PlayerCollisionObject(const PlayerCollisionObject& obj) :
    super(obj._priority),
    _player_com() {
}

my::PlayerCollisionObject::~PlayerCollisionObject() {
}

std::string my::PlayerCollisionObject::GetType(void) const {
    return "PlayerCollisionObject";
}

std::optional<Mof::CSphere> my::PlayerCollisionObject::GetSphere(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CSphere(pos, _player_com.lock()->GetVolume());
}

std::optional<Mof::CBoxAABB> my::PlayerCollisionObject::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::PlayerCollisionObject::GetRay(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> my::PlayerCollisionObject::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::PlayerCollisionObject::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::PlayerCollisionObject::Initialize(void) {
    super::Initialize();
    _player_com = super::GetOwner()->GetComponent<my::PlayerComponent>();
    return true;
}

std::shared_ptr<my::Component> my::PlayerCollisionObject::Clone(void) {
    return std::make_shared<my::PlayerCollisionObject>(*this);
}

void my::PlayerCollisionObject::CollisionStage(Mof::LPMeshContainer mesh) {
    if (!this->GetRay().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetRay().value().CollisionMesh(mesh, info)) {
        float height = _player_com.lock()->GetHeight();
        if (info.d <= height) {
            auto pos = super::GetOwner()->GetPosition();
            pos.y += height - info.d;
            super::GetOwner()->SetPosition(pos);
        } // if
    } // if
}