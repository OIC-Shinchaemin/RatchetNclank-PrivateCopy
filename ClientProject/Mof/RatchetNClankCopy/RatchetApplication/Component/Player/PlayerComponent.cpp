#include "PlayerComponent.h"

#include "../../Gamepad.h"
#include "../../Actor/Character/Player.h"
#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"
#include "../../Component/Player/PlayerStateComponent.h"
#include "../Collision/Object/PlayerCollisionComponent.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../../UI/LockOnCursorMenu.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../Game/GameSystem/GameQuest.h"


ratchet::PlayerComponent::PlayerComponent(int priority) :
    super(priority),
    _target(),
    _state_com(),
    _next_terrain()
    //,
    //_action_enable()
{
}

ratchet::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _target(),
    _state_com(),
    _next_terrain()
    //,
    //_action_enable() 
{
}

ratchet::PlayerComponent::~PlayerComponent() {
}

void ratchet::PlayerComponent::SetTarget(const std::shared_ptr<ratchet::Actor>& ptr) {
    this->_target = ptr;
}

void ratchet::PlayerComponent::SetNextTerrain(const std::string& terrain) {
    this->_next_terrain = terrain;
}

std::string ratchet::PlayerComponent::GetType(void) const {
    return "PlayerComponent";
}

std::weak_ptr<ratchet::Actor> ratchet::PlayerComponent::GetTarget(void) const {
    return this->_target;
}

std::string ratchet::PlayerComponent::GetNextTerrain(void) const {
    return this->_next_terrain;
}

bool ratchet::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::PlayerStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    if (velocity_com) {
        velocity_com->SetGravity(9.8f);
    } // if
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if


    auto coll_com = super::GetOwner()->GetComponent<ratchet::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::CollisionComponentType::kShipCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        if (auto canvas = _ui_canvas.lock()) {
            canvas->RemoveElement("EquipmentWeaponMenu");
            canvas->RemoveElement("QuickChangeMenu");
        } // if
        super::GetOwner()->End();
        return true;
    }));

    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::CollisionComponentType::kWaterFlowCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        if (this->GetNextTerrain() == "WaterFlow") {
            auto owner = super::GetOwner();
            auto velocity_com = owner->GetComponent<ratchet::VelocityComponent>();
            auto velocity = velocity_com->GetVelocity() * def::kDeltaTime;
            velocity.y = 0.0f;
            owner->SetPosition(owner->GetPosition() - velocity);
        } // if
        return true;
    }));

    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::CollisionComponentType::kShopCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<ratchet::Player>(super::GetOwner());
        player->GetQuestSubject()->Notify(ratchet::GameQuest::Type::ShopAccessStart);
        player->PushNotificationableSubject("ShopSystem");

        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Exit,
                               ratchet::CollisionComponentType::kShopCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<ratchet::Player>(super::GetOwner());
        player->GetQuestSubject()->Notify(ratchet::GameQuest::Type::ShopAccessEnd);
        player->PopNotificationableSubject("ShopSystem");
        return true;
    }));




    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
        auto menu = std::make_shared<ratchet::LockOnCursorMenu>("LockOnCursorMenu");
        menu->SetResourceManager(_resource_manager);
        _observable.AddObserver(menu);
        canvas->AddElement(menu);
    } // if
    return true;
}

bool ratchet::PlayerComponent::Update(float delta_time) {
    _next_terrain = "";

    if (auto target = _target.lock()) {
        auto ENEMY_com = target->GetComponent<super>();
        auto pos = target->GetPosition();
        pos.y += ENEMY_com->GetHeight();
        _observable.Notify(pos);
    } // if
    else {
        _observable.Notify(std::optional<Mof::CVector3>());
    } // else 
    return true;
}

bool ratchet::PlayerComponent::Release(void) {
    super::Release();
    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
    } // if
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::PlayerComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerComponent>(*this);
}