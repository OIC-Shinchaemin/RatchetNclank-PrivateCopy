#include "PlayerComponent.h"

#include "../../Gamepad.h"
#include "../../Actor/Ship/Ship.h"
#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"
#include "../../Component/Player/PlayerStateComponent.h"
#include "../Collision/Object/PlayerCollisionComponent.h"
#include "../../UI/LockOnCursorMenu.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"


my::PlayerComponent::PlayerComponent(int priority) :
    super(priority),
    _target(),
    _state_com() {
    super::_volume = 0.5f;
    super::_height = 1.0f;
}

my::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _target(),
    _state_com() {
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

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();

    velocity_com->SetGravity(9.8f);
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if


    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Stay,
                               "ShipCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->Notify("ShipCollision", super::GetOwner());

        if (std::dynamic_pointer_cast<my::Ship>(std::any_cast<std::shared_ptr<my::Actor>>(in.target))->IsEnable()) {
            super::GetOwner()->GetComponent<my::MeshComponent>()->Hide();
        } // if
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
    return true;
}