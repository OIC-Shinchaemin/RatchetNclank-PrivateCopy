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


ratchet::component::player::PlayerComponent::PlayerComponent(int priority) :
    super(priority),
    _target(),
    _state_com(),
    _next_terrain() {
}

ratchet::component::player::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _target(),
    _state_com(),
    _next_terrain() {
}

ratchet::component::player::PlayerComponent::~PlayerComponent() {
}

void ratchet::component::player::PlayerComponent::SetTarget(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_target = ptr;
}

void ratchet::component::player::PlayerComponent::SetNextTerrain(const std::string& terrain) {
    this->_next_terrain = terrain;
}

std::string ratchet::component::player::PlayerComponent::GetType(void) const {
    return "PlayerComponent";
}

std::weak_ptr<ratchet::actor::Actor> ratchet::component::player::PlayerComponent::GetTarget(void) const {
    return this->_target;
}

std::string ratchet::component::player::PlayerComponent::GetNextTerrain(void) const {
    return this->_next_terrain;
}

bool ratchet::component::player::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerStateComponent>();
    auto velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    if (velocity_com) {
        velocity_com->SetGravity(9.8f);
    } // if
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if


    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::PlayerCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kShipCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        if (auto canvas = _ui_canvas.lock()) {
            canvas->RemoveElement("EquipmentWeaponMenu");
            canvas->RemoveElement("QuickChangeMenu");
        } // if

        
        super::GetOwner()->End();
        return true;
    }));

    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kWaterFlowCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        if (this->GetNextTerrain() == "WaterFlow") {
            auto owner = super::GetOwner();
            auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
            auto velocity = velocity_com->GetVelocity() * def::kDeltaTime;
            velocity.y = 0.0f;
            owner->SetPosition(owner->GetPosition() - velocity);
        } // if
        return true;
    }));

    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kShopCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
        player->GetQuestSubject()->Notify(ratchet::game::gamesystem::GameQuest::Type::ShopAccessStart);
        player->PushNotificationableSubject("ShopSystem");

        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Exit,
                               ratchet::component::collision::CollisionComponentType::kShopCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
        player->GetQuestSubject()->Notify(ratchet::game::gamesystem::GameQuest::Type::ShopAccessEnd);
        player->PopNotificationableSubject("ShopSystem");
        return true;
    }));




    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
        auto menu = std::make_shared<ratchet::ui::LockOnCursorMenu>("LockOnCursorMenu");
        menu->SetResourceManager(_resource_manager);
        _observable.AddObserver(menu);
        canvas->AddElement(menu);
    } // if
    return true;
}

bool ratchet::component::player::PlayerComponent::Update(float delta_time) {
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

bool ratchet::component::player::PlayerComponent::Release(void) {
    super::Release();
    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::PlayerComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::PlayerComponent>(*this);
}