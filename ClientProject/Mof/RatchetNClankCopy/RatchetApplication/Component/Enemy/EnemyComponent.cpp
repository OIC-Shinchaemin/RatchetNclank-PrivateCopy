#include "EnemyComponent.h"

#include "../../Gamepad.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../VelocityComponent.h"
#include "../Enemy/EnemyDamageComponent.h"
#include "../SightRecognitionComponent.h"
#include "../Collision/Object/EnemyCollisionComponent.h"
#include "../Collision/Object/SightCollisionComponent.h"
#include "../../Actor/Character/Enemy.h"


ratchet::EnemyComponent::EnemyComponent(int priority) :
    super(priority),
    _velocity_timer(),
    _target(),
    _velocity_com() {
}

ratchet::EnemyComponent::EnemyComponent(const EnemyComponent& obj) :
    super(obj),
    _velocity_timer(),
    _target(),
    _velocity_com() {
}

ratchet::EnemyComponent::~EnemyComponent() {
}

void ratchet::EnemyComponent::SetTarget(const std::shared_ptr<ratchet::Actor>& ptr) {
    this->_target = ptr;
}

std::string ratchet::EnemyComponent::GetType(void) const {
    return "EnemyComponent";
}

std::weak_ptr<ratchet::Actor> ratchet::EnemyComponent::GetTarget(void) const {
    return this->_target;
}

std::optional<Mof::CVector3> ratchet::EnemyComponent::GetTargetPosition(void) const {
    if (auto target = this->GetTarget().lock()) {
        auto pos = target->GetPosition();
        float player_height = target->GetComponent<ratchet::CharacterComponent>()->GetHeight();
        pos.y += player_height;
        return pos;
    } // if
    return std::optional<Mof::CVector3>();
}

float ratchet::EnemyComponent::GetHomeDistance(void) const {
    return 2.5f;
}

bool ratchet::EnemyComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _velocity_timer.Initialize(1.0f, true);

    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetSleep(true);
        velocity_com->SetGravity(0.0f);
    } // if


    auto coll_com = super::GetOwner()->GetComponent<ratchet::EnemyCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::CollisionComponentType::kEnemyCollisionComponent,
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
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

    auto sight_coll = super::GetOwner()->GetComponent<ratchet::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                                 "PlayerCollisionComponent",
                                 ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        auto target = in.target.lock();
        this->SetTarget(target);
        return true;
    }));
    sight_coll->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Exit,
                                 "PlayerCollisionComponent",
                                 ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        this->SetTarget(nullptr);
        return true;
    }));
    return true;
}

bool ratchet::EnemyComponent::Update(float delta_time) {
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetUseGravity(false);
    } // if

    if (_velocity_timer.Tick(delta_time)) {
        if (auto velocity_com = _velocity_com.lock()) {
            bool in_camera_range = super::GetOwner()->InCameraRange();
            if (in_camera_range) {
                auto owner = std::dynamic_pointer_cast<ratchet::Enemy>(super::GetOwner());
                owner->GetQuestSubject()->Notify(ratchet::game::gamesystem::GameQuest::GameQuest(ratchet::game::gamesystem::GameQuest::Type::EnemyDestroy));
                velocity_com->SetSleep(false);
                velocity_com->SetGravity(1.0f);
            } // if
            else {
                auto owner = std::dynamic_pointer_cast<ratchet::Enemy>(super::GetOwner());
                owner->GetQuestSubject()->Notify(ratchet::game::gamesystem::GameQuest::GameQuest(ratchet::game::gamesystem::GameQuest::Type::ToFront));
                velocity_com->SetSleep(true);
                velocity_com->SetGravity(0.0f);
            } // else
        } // if
    } // if
    return true;
}

bool ratchet::EnemyComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::EnemyComponent::Clone(void) {
    return std::make_shared<ratchet::EnemyComponent>(*this);
}