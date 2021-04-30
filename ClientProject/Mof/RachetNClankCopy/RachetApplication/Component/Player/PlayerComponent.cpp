#include "PlayerComponent.h"

#include "../../Gamepad.h"
#include "../../Component/HpComponent.h"
#include "../../Component/VelocityComponent.h"
#include "../Player/PlayerIdleComponent.h"
#include "../Player/PlayerMoveComponent.h"
#include "../Player/PlayerDamageComponent.h"
#include "../Collision/Object/PlayerCollisionComponent.h"
#include "../../UI/LockOnCursorMenu.h"


my::PlayerComponent::PlayerComponent(int priority) :
    super(priority),
    _target(),
    _state_com(),
    _idle_com(),
    _move_com(),
    _damage_com() {
    super::_volume = 0.5f;
    super::_height = 1.0f;
}

my::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _target(),
    _state_com(),
    _idle_com(),
    _move_com(),
    _damage_com() {
}

my::PlayerComponent::~PlayerComponent() {
}

void my::PlayerComponent::SetTarget(const std::shared_ptr<my::Actor>& ptr) {
    this->_target = ptr;
}

std::string my::PlayerComponent::GetType(void) const {
    return "PlayerComponent";
}

std::weak_ptr<my::Actor> my::PlayerComponent::GetTarget(void) const {
    return this->_target;
}

bool my::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _idle_com = super::GetOwner()->GetComponent<my::PlayerIdleComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    _damage_com = super::GetOwner()->GetComponent<my::PlayerDamageComponent>();

    velocity_com->SetGravity(9.8f);

    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Stay,
                               "ShipCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->Notify("ShipCollision", super::GetOwner());
        return true;
    }));

    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
        auto menu = std::make_shared<my::LockOnCursorMenu>("LockOnCursorMenu");
        menu->SetResourceManager(_resource_manager);
        _observable.AddObserver(menu);
        canvas->AddElement(menu);
    } // if
    return true;
}

bool my::PlayerComponent::Update(float delta_time) {
    if (auto target = _target.lock()) {
        auto enemy_com = target->GetComponent<super>();
        auto pos = target->GetPosition();
        pos.y += enemy_com->GetHeight();
        _observable.Notify(pos);
    } // if
    else {
        _observable.Notify(std::optional<Mof::CVector3>());
    } // else 
    return true;
}

bool my::PlayerComponent::Release(void) {
    super::Release();
    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
    } // if
    return true;
}

std::shared_ptr<my::Component> my::PlayerComponent::Clone(void) {
    return std::make_shared<my::PlayerComponent>(*this);
}

bool my::PlayerComponent::DebugRender(void) {
    auto pos = super::GetOwner()->GetPosition();

    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "pos.x = %f", pos.x);
    ::CGraphicsUtilities::RenderString(10.0f, 30.0f, "pos.y = %f", pos.y);
    ::CGraphicsUtilities::RenderString(10.0f, 50.0f, "pos.z = %f", pos.z);
    return true;
}