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


rachet::PlayerComponent::PlayerComponent(int priority) :
    super(priority),
    _target(),
    _state_com(),
    _next_terrain()
    //,
    //_action_enable()
{
}

rachet::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _target(),
    _state_com(),
    _next_terrain()
    //,
    //_action_enable() 
{
}

rachet::PlayerComponent::~PlayerComponent() {
}

void rachet::PlayerComponent::SetTarget(const std::shared_ptr<rachet::Actor>& ptr) {
    this->_target = ptr;
}

void rachet::PlayerComponent::SetNextTerrain(const std::string& terrain) {
    this->_next_terrain = terrain;
}

std::string rachet::PlayerComponent::GetType(void) const {
    return "PlayerComponent";
}

std::weak_ptr<rachet::Actor> rachet::PlayerComponent::GetTarget(void) const {
    return this->_target;
}

std::string rachet::PlayerComponent::GetNextTerrain(void) const {
    return this->_next_terrain;
}

bool rachet::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<rachet::PlayerStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    if (velocity_com) {
        velocity_com->SetGravity(9.8f);
    } // if
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if


    auto coll_com = super::GetOwner()->GetComponent<rachet::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Stay,
                               rachet::CollisionComponentType::kShipCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        if (auto canvas = _ui_canvas.lock()) {
            canvas->RemoveElement("EquipmentWeaponMenu");
            canvas->RemoveElement("QuickChangeMenu");
        } // if
        super::GetOwner()->End();
        return true;
    }));

    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Stay,
                               rachet::CollisionComponentType::kWaterFlowCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        if (this->GetNextTerrain() == "WaterFlow") {
            auto owner = super::GetOwner();
            auto velocity_com = owner->GetComponent<rachet::VelocityComponent>();
            auto velocity = velocity_com->GetVelocity() * def::kDeltaTime;
            velocity.y = 0.0f;
            owner->SetPosition(owner->GetPosition() - velocity);
        } // if
        return true;
    }));

    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               rachet::CollisionComponentType::kShopCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<rachet::Player>(super::GetOwner());
        player->GetQuestSubject()->Notify(rachet::GameQuest::Type::ShopAccessStart);
        player->PushNotificationableSubject("ShopSystem");

        return true;
    }));
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Exit,
                               rachet::CollisionComponentType::kShopCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<rachet::Player>(super::GetOwner());
        player->GetQuestSubject()->Notify(rachet::GameQuest::Type::ShopAccessEnd);
        player->PopNotificationableSubject("ShopSystem");
        return true;
    }));




    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
        auto menu = std::make_shared<rachet::LockOnCursorMenu>("LockOnCursorMenu");
        menu->SetResourceManager(_resource_manager);
        _observable.AddObserver(menu);
        canvas->AddElement(menu);
    } // if
    return true;
}

bool rachet::PlayerComponent::Update(float delta_time) {
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

bool rachet::PlayerComponent::Release(void) {
    super::Release();
    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
    } // if
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerComponent::Clone(void) {
    return std::make_shared<rachet::PlayerComponent>(*this);
}