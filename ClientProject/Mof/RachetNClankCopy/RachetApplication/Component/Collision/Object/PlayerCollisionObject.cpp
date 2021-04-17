#include "PlayerCollisionObject.h"

#include "../../Player/PlayerComponent.h"


my::PlayerCollisionObject::PlayerCollisionObject(int priority) :
    super(priority),
    _player_com(){
}

my::PlayerCollisionObject::PlayerCollisionObject(const PlayerCollisionObject& obj) :
    super(obj._priority) ,
    _player_com(){
}

my::PlayerCollisionObject::~PlayerCollisionObject() {
}

std::string my::PlayerCollisionObject::GetType(void) const {
    return "PlayerCollisionObject";
}

std::optional<Mof::CSphere> my::PlayerCollisionObject::GetSphere(void) {
    _ASSERT_EXPR(!_player_com.expired(),L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
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
    return std::optional<Mof::CRay3D>();
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
