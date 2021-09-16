#include "PlayerComponent.h"

#include "../../Gamepad.h"
#include "../../Actor/Character/Player.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"
#include "../../Component/Player/PlayerStateComponent.h"
#include "../Collision/Object/PlayerCollisionComponent.h"
#include "../Collision/CollisionComponentDefine.h"
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
    _transform_com(),
    _velocity_com(),
    _camera_com(),
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

bool ratchet::component::player::PlayerComponent::IsContactMode(void) const {
    return this->_contact_mode;
}

bool ratchet::component::player::PlayerComponent::HasTalkTarget(void) const {
    if (!_talk_target.expired()) {
        return true;
    } // if
    return false;
}

bool ratchet::component::player::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _state_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerStateComponent>();
    _transform_com = super::GetOwner()->GetComponent<ratchet::component::TransformComponent>();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _camera_com = super::GetOwner()->GetComponent<ratchet::component::CameraComponent>();

    auto velocity_com = _velocity_com.lock();
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


    {
        coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                                   ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent,
                                   ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
            auto target = in.target.lock();
            Mof::CVector3 vec = super::GetOwner()->GetPosition() - target->GetPosition();
            auto length = (this->GetVolume() * 2.0f) - vec.Length();
            vec.Normal(vec);
            // —£‚ê‚é
            auto diff = vec * length * 0.5f; diff.y = 0.0f;

            auto pos = super::GetOwner()->GetPosition();
            super::GetOwner()->SetPosition(pos + diff);
            return true;
        }));

    }

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



    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kKingCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        _talk_target = std::dynamic_pointer_cast<ratchet::actor::character::King>(in.target.lock());
        _contact_mode = true;
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Exit,
                               ratchet::component::collision::CollisionComponentType::kKingCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        _talk_target.reset();
        _contact_mode = false;
        return true;
    }));



    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kWallCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
        auto velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();

        auto v = velocity_com->GetVelocity();
        float d = 3.0f;

        auto add = Mof::CVector3(-v.x, 0.0f, -v.z) * d;
        velocity_com->AddVelocityForce(add);

        if (auto transform = _transform_com.lock()) {
            //player->SetPosition(transform->GetPreviousPosition());
        } // if
        OutputDebugString("kWallCollisionComponent‚†");
        puts("kWallCollisionComponent‚†");
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
    auto velocity_com = _velocity_com.lock();
    auto camera_com = _camera_com.lock();

    if (velocity_com && camera_com) {
        auto v = velocity_com->GetVelocity();
        float threshold = 0.000005f;
        if (Mof::CVector2(v.x, v.z).Length() < threshold) {
            camera_com->GetCameraController()->GetService()->SetUseSpring(true);
        } // if
        else {
            camera_com->GetCameraController()->GetService()->SetUseSpring(false);
        } // else
    } // if

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

void ratchet::component::player::PlayerComponent::TalkToTarget(void) {
    if (auto target = _talk_target.lock()) {
        target->Talk();
        super::GetOwner()->Sleep();
    } // if
}

#ifdef _DEBUG
bool ratchet::component::player::PlayerComponent::DebugRender(void) {
    if (this->IsContactMode()) {
        ::CGraphicsUtilities::RenderString(600.0f, 600.0f, "action button enable");
    } // if
    else {
        ::CGraphicsUtilities::RenderString(600.0f, 600.0f, "action button disable");
    } // else


    auto camera_com = _camera_com.lock();
    auto v = camera_com->GetVelocity();
    ::CGraphicsUtilities::RenderString(500.0f, 610.0f, "camera_com GetVelocity()2 v = %f",  Mof::CVector2(v.x, v.z).Length());
    ::CGraphicsUtilities::RenderString(500.0f, 630.0f, "camera_com GetVelocity() x = %f", v.x);
    ::CGraphicsUtilities::RenderString(500.0f, 650.0f, "camera_com GetVelocity() y = %f", v.y);
    ::CGraphicsUtilities::RenderString(500.0f, 670.0f, "camera_com GetVelocity() z = %f", v.z);
    ::CGraphicsUtilities::RenderString(500.0f, 690.0f, "camera_com GetVelocity() v = %f", v.Length());
    return false;
}
#endif // _DEBUG