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
#include "../../Game/GameManager.h"


void ratchet::component::player::PlayerComponent::CacheComponent(void) {
    _state_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _camera_com = super::GetOwner()->GetComponent<ratchet::component::CameraComponent>();
    _coll_volume_com = super::GetOwner()->GetComponent<ratchet::component::collision::PlayerCollisionComponent>();
}

void ratchet::component::player::PlayerComponent::CollisionFunctionBarrack(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kBarrackCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto owner = super::GetOwner();
        auto pos = owner->GetPosition();
        auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
        Mof::CVector3 velocity = (velocity_com->GetVelocity()) * def::kDeltaTime;

        pos.x += -velocity.x;
        pos.z += -velocity.z;
        super::GetOwner()->SetPosition(pos);
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kBarrackCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto owner = super::GetOwner();
        auto pos = owner->GetPosition();
        auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
        Mof::CVector3 velocity = (velocity_com->GetVelocity()) * def::kDeltaTime;

        pos.x += -velocity.x;
        pos.z += -velocity.z;
        super::GetOwner()->SetPosition(pos);
        return true;
    }));
}

void ratchet::component::player::PlayerComponent::CollisionFunctionBarricade(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kBarricadeCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto owner = super::GetOwner();
        auto pos = owner->GetPosition();
        auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
        Mof::CVector3 velocity = (velocity_com->GetVelocity()) * def::kDeltaTime;

        pos.x += -velocity.x;
        pos.z += -velocity.z;
        super::GetOwner()->SetPosition(pos);
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kBarricadeCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto owner = super::GetOwner();
        auto pos = owner->GetPosition();
        auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
        Mof::CVector3 velocity = (velocity_com->GetVelocity()) * def::kDeltaTime;

        pos.x += -velocity.x;
        pos.z += -velocity.z;
        super::GetOwner()->SetPosition(pos);
        return true;
    }));
}

void ratchet::component::player::PlayerComponent::CollisionFunctionFence(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kFenceCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto owner = super::GetOwner();
        auto pos = owner->GetPosition();
        auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
        Mof::CVector3 velocity = (velocity_com->GetVelocity()) * def::kDeltaTime;

        pos.x += -velocity.x;
        pos.z += -velocity.z;
        super::GetOwner()->SetPosition(pos);
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kFenceCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto owner = super::GetOwner();
        auto pos = owner->GetPosition();
        auto velocity_com = owner->GetComponent<ratchet::component::VelocityComponent>();
        Mof::CVector3 velocity = (velocity_com->GetVelocity()) * def::kDeltaTime;

        pos.x += -velocity.x;
        pos.z += -velocity.z;
        super::GetOwner()->SetPosition(pos);
        return true;
    }));
}

void ratchet::component::player::PlayerComponent::CollisionFunctionKing(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kKingCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        _talk_target = std::dynamic_pointer_cast<ratchet::actor::character::Character>(in.target.lock());
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
}

void ratchet::component::player::PlayerComponent::CollisionFunctionQueen(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               ratchet::component::collision::CollisionComponentType::kQueenCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        _talk_target = std::dynamic_pointer_cast<ratchet::actor::character::Character>(in.target.lock());
        _contact_mode = true;
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Exit,
                               ratchet::component::collision::CollisionComponentType::kQueenCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        _talk_target.reset();
        _contact_mode = false;
        return true;
    }));
}

void ratchet::component::player::PlayerComponent::CollisionFunctionScarecrow(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
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

void ratchet::component::player::PlayerComponent::CollisionFunctionShop(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
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
}

void ratchet::component::player::PlayerComponent::CollisionFunctionShip(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kShipCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        if (auto canvas = _ui_canvas.lock()) {
            canvas->RemoveElement("EquipmentWeaponMenu");
            canvas->RemoveElement("QuickChangeMenu");
        } // if

        if (event::EventReferenceTable::Singleton().Exist("GameManager")) {
            auto game = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::game::GameManager>>("GameManager");
            auto help_desk = game->GetHelpDesk();
            help_desk->RegisterQuest(ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::None));
        } // if

        super::GetOwner()->End();
        return true;
    }));

}

void ratchet::component::player::PlayerComponent::CollisionFunctionWall(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kWallCollisionComponent,
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto player = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
        auto velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();

        auto v = velocity_com->GetVelocity();
        float d = 3.0f;

        auto add = Mof::CVector3(-v.x, 0.0f, -v.z) * d;
        velocity_com->AddVelocityForce(add);
        return true;
    }));
}

void ratchet::component::player::PlayerComponent::CollisionFunctionWaterFlow(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& coll_com) {
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
}

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
    _velocity_com(),
    _camera_com(),
    _coll_volume_com(),
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

std::shared_ptr<ratchet::actor::character::Player> ratchet::component::player::PlayerComponent::GetOwnerCastd(void) const {
    return std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
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
    this->CacheComponent();

    auto velocity_com = _velocity_com.lock();
    if (velocity_com) {
        velocity_com->SetGravity(9.8f);
        velocity_com->SetAngularDrag(0.80f);
    } // if
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::PlayerCollisionComponent>();
    this->CollisionFunctionBarrack(coll_com);
    this->CollisionFunctionBarricade(coll_com);
    this->CollisionFunctionFence(coll_com);
    this->CollisionFunctionKing(coll_com);
    this->CollisionFunctionQueen(coll_com);
    this->CollisionFunctionScarecrow(coll_com);
    //this->CollisionFunctionShop(coll_com);
    this->CollisionFunctionShip(coll_com);
    this->CollisionFunctionWall(coll_com);
    this->CollisionFunctionWaterFlow(coll_com);

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

    camera_com->GetCameraController()->GetService()->SetUseSpring(true);

    if (velocity_com && camera_com) {
        auto v = velocity_com->GetVelocity();
        //float threshold = 0.000005f;
        float threshold = 0.001f;


        //if (!_coll_volume_com.lock()->IsOnElevator()) {
        //    if (Mof::CVector2(v.x, v.z).Length() < threshold) {
        //        camera_com->GetCameraController()->GetService()->SetUseSpring(true);
        //    } // if
        //    else {
        //        camera_com->GetCameraController()->GetService()->SetUseSpring(false);
        //    } // else
        //} // if

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
        target->SetTalkedTarget(this->GetOwnerCastd());
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


    auto velocity = _velocity_com.lock()->GetVelocity();
    
    ::CGraphicsUtilities::RenderString(500.0f, 430.0f, "velocity.x = %f", velocity.x);
    ::CGraphicsUtilities::RenderString(500.0f, 450.0f, "velocity y = %f", velocity.y);
    ::CGraphicsUtilities::RenderString(500.0f, 470.0f, "velocity z = %f", velocity.z);


    auto camera_com = _camera_com.lock();
    camera_com->GetCameraController()->GetService()->SetUseSpring(false);

    auto p = camera_com->GetPosition();
    auto v = camera_com->GetVelocity();



    ::CGraphicsUtilities::RenderString(500.0f, 530.0f, "camera_com GetPosition() x = %f", p.x);
    ::CGraphicsUtilities::RenderString(500.0f, 550.0f, "camera_com GetPosition() y = %f", p.y);
    ::CGraphicsUtilities::RenderString(500.0f, 570.0f, "camera_com GetPosition() z = %f", p.z);

    ::CGraphicsUtilities::RenderString(500.0f, 610.0f, "camera_com GetVelocity()2 v = %f", Mof::CVector2(v.x, v.z).Length());
    ::CGraphicsUtilities::RenderString(500.0f, 630.0f, "camera_com GetVelocity() x = %f", v.x);
    ::CGraphicsUtilities::RenderString(500.0f, 650.0f, "camera_com GetVelocity() y = %f", v.y);
    ::CGraphicsUtilities::RenderString(500.0f, 670.0f, "camera_com GetVelocity() z = %f", v.z);
    ::CGraphicsUtilities::RenderString(500.0f, 690.0f, "camera_com GetVelocity() v = %f", v.Length());
    return false;
}
#endif // _DEBUG