#include "EnemyComponent.h"

#include "../../Gamepad.h"
#include "../Collision/Object/CollisionComponentDefine.h"
#include "../VelocityComponent.h"
#include "../Enemy/EnemyDamageComponent.h"
#include "../SightRecognitionComponent.h"
#include "../Collision/Object/EnemyCollisionComponent.h"
#include "../Collision/Object/SightCollisionComponent.h"
#include "../../Actor/Character/Enemy.h"


rachet::EnemyComponent::EnemyComponent(int priority) :
    super(priority),
    _velocity_timer(),
    _target(),
    _velocity_com() {
}

rachet::EnemyComponent::EnemyComponent(const EnemyComponent& obj) :
    super(obj),
    _velocity_timer(),
    _target(),
    _velocity_com() {
}

rachet::EnemyComponent::~EnemyComponent() {
}

void rachet::EnemyComponent::SetTarget(const std::shared_ptr<rachet::Actor>& ptr) {
    this->_target = ptr;
}

std::string rachet::EnemyComponent::GetType(void) const {
    return "EnemyComponent";
}

std::weak_ptr<rachet::Actor> rachet::EnemyComponent::GetTarget(void) const {
    return this->_target;
}

std::optional<Mof::CVector3> rachet::EnemyComponent::GetTargetPosition(void) const {
    if (auto target = this->GetTarget().lock()) {
        auto pos = target->GetPosition();
        float player_height = target->GetComponent<rachet::CharacterComponent>()->GetHeight();
        pos.y += player_height;
        return pos;
    } // if
    return std::optional<Mof::CVector3>();
}

float rachet::EnemyComponent::GetHomeDistance(void) const {
    return 2.5f;
}

bool rachet::EnemyComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _velocity_timer.Initialize(1.0f, true);

    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetSleep(true);
        velocity_com->SetGravity(0.0f);
    } // if


    auto coll_com = super::GetOwner()->GetComponent<rachet::EnemyCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Stay,
                               rachet::CollisionComponentType::kEnemyCollisionComponent,
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
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

    auto sight_coll = super::GetOwner()->GetComponent<rachet::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                                 "PlayerCollisionComponent",
                                 rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        auto target = in.target.lock();
        this->SetTarget(target);
        return true;
    }));
    sight_coll->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Exit,
                                 "PlayerCollisionComponent",
                                 rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        this->SetTarget(nullptr);
        return true;
    }));
    return true;
}

bool rachet::EnemyComponent::Update(float delta_time) {
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetUseGravity(false);
    } // if

    if (_velocity_timer.Tick(delta_time)) {
        if (auto velocity_com = _velocity_com.lock()) {
            bool in_camera_range = super::GetOwner()->InCameraRange();
            if (in_camera_range) {
                auto owner = std::dynamic_pointer_cast<rachet::Enemy>(super::GetOwner());
                owner->GetQuestSubject()->Notify(rachet::GameQuest::GameQuest(rachet::GameQuest::Type::EnemyDestroy));
                velocity_com->SetSleep(false);
                velocity_com->SetGravity(1.0f);
            } // if
            else {
                auto owner = std::dynamic_pointer_cast<rachet::Enemy>(super::GetOwner());
                owner->GetQuestSubject()->Notify(rachet::GameQuest::GameQuest(rachet::GameQuest::Type::ToFront));
                velocity_com->SetSleep(true);
                velocity_com->SetGravity(0.0f);
            } // else
        } // if
    } // if
    return true;
}

bool rachet::EnemyComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::EnemyComponent::Clone(void) {
    return std::make_shared<rachet::EnemyComponent>(*this);
}