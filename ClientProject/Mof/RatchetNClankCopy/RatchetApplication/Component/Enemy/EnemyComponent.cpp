#include "EnemyComponent.h"

#include "../../Gamepad.h"
#include "../Collision/CollisionComponentDefine.h"
#include "../VelocityComponent.h"
#include "../Enemy/EnemyDamageComponent.h"
#include "../SightRecognitionComponent.h"
#include "../Collision/Object/EnemyCollisionComponent.h"
#include "../Collision/Object/SightCollisionComponent.h"
#include "../../Actor/Character/Enemy.h"

void ratchet::component::enemy::EnemyComponent::DamageEffectEmit(std::shared_ptr<ratchet::actor::Actor> actor) {
    auto camera_pos = CGraphicsUtilities::GetCamera()->GetViewPosition();
    auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Enemy>(super::GetOwner());
    auto target_pos = actor->GetPosition();
    auto pos = (owner->GetPosition() + target_pos) * 0.5f;
    auto diff = Mof::CVector3(camera_pos - pos);
    diff.Normal(diff);
    pos += diff * super::GetVolume() * 2.0f;
    pos.y += this->GetHeight();

    auto info = ratchet::effect::Effect::Info();
    auto init_pos_offset = Mof::CVector3();
    auto init_scale = Mof::CVector3(1.0f, 1.0f, 1.0f);
    info.init_param.life_duration = 1.0f;
    info.init_param.color = Mof::CVector4(1.0f, 1.0f, 1.0f, 1.0f);
    info.update_param.color = Mof::CVector4(0.0f, 0.0f, 0.0f, -0.02f);
    info.environment_param.use_gravity = false;
    info.environment_param.use_velocity_drag = true;
    info.environment_param.velocity_drag = 0.5f;

    for (int i = 0, n = 5; i < n; i++) {
        info.init_param.transform.position = pos + init_pos_offset;
        info.init_param.transform.scale = init_scale;
        info.update_param.rotate = Mof::CVector3(0.0f, 1.0f, 0.0f);
        owner->GetEffectEmitter()->Emit(info);

        init_pos_offset = Mof::CVector3(
            ut::GenerateRandomF(-1.0f, 1.0f),
            ut::GenerateRandomF(-1.0f, 1.0f),
            ut::GenerateRandomF(-1.0f, 1.0f)
        );
        init_scale = Mof::CVector3(
            ut::GenerateRandomF(0.4f, 0.7f),
            ut::GenerateRandomF(0.4f, 0.7f),
            ut::GenerateRandomF(0.4f, 0.7f)
        );
        info.update_param.velocity = Mof::CVector3(
            ut::GenerateRandomF(-0.3f, 0.3f),
            0.4f,
            ut::GenerateRandomF(-0.3f, 0.3f)
        );
        info.update_param.rotate = Mof::CVector3(
            0.0f, ut::GenerateRandomF(-1.0f, 1.0f), 0.0f
        );
        info.update_param.scale = Mof::CVector3(-0.05f, -0.05f, -0.05f);
        info.environment_param.use_gravity = true;
        info.environment_param.gravity_scale = 0.01f;
    } // for
}

ratchet::component::enemy::EnemyComponent::EnemyComponent(int priority) :
    super(priority),
    _velocity_timer(),
    _target(),
    _velocity_com() {
}

ratchet::component::enemy::EnemyComponent::EnemyComponent(const EnemyComponent& obj) :
    super(obj),
    _velocity_timer(),
    _target(),
    _velocity_com() {
}

ratchet::component::enemy::EnemyComponent::~EnemyComponent() {
}

void ratchet::component::enemy::EnemyComponent::SetTarget(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_target = ptr;
}

std::string ratchet::component::enemy::EnemyComponent::GetType(void) const {
    return "EnemyComponent";
}

std::weak_ptr<ratchet::actor::Actor> ratchet::component::enemy::EnemyComponent::GetTarget(void) const {
    return this->_target;
}

std::optional<Mof::CVector3> ratchet::component::enemy::EnemyComponent::GetTargetPosition(void) const {
    if (auto target = this->GetTarget().lock()) {
        auto pos = target->GetPosition();
        float player_height = target->GetComponent<ratchet::component::CharacterComponent>()->GetHeight();
        pos.y += player_height;
        return pos;
    } // if
    return std::optional<Mof::CVector3>();
}

float ratchet::component::enemy::EnemyComponent::GetHomeDistance(void) const {
    return 2.5f;
}

bool ratchet::component::enemy::EnemyComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _velocity_timer.Initialize(1.0f, true);

    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetSleep(true);
        velocity_com->SetGravity(0.0f);
    } // if


    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::EnemyCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                               ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent,
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

    auto sight_coll = super::GetOwner()->GetComponent<ratchet::component::collision::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                                 "PlayerCollisionComponent",
                                 ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        auto target = in.target.lock();
        this->SetTarget(target);
        return true;
    }));
    sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Exit,
                                 "PlayerCollisionComponent",
                                 ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        this->SetTarget(nullptr);
        return true;
    }));
    return true;
}

bool ratchet::component::enemy::EnemyComponent::Update(float delta_time) {
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetUseGravity(false);
    } // if

    if (_velocity_timer.Tick(delta_time)) {
        if (auto velocity_com = _velocity_com.lock()) {
            bool in_camera_range = super::GetOwner()->InCameraRange();
            if (in_camera_range) {
                auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Enemy>(super::GetOwner());
                owner->GetQuestSubject()->Notify(ratchet::game::gamesystem::GameQuest::GameQuest(ratchet::game::gamesystem::GameQuest::Type::EnemyDestroy));
                velocity_com->SetSleep(false);
                velocity_com->SetGravity(1.0f);
            } // if
            else {
                auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Enemy>(super::GetOwner());
//                owner->GetQuestSubject()->Notify(ratchet::game::gamesystem::GameQuest::GameQuest(ratchet::game::gamesystem::GameQuest::Type::ToFront));
                velocity_com->SetSleep(true);
                velocity_com->SetGravity(0.0f);
            } // else
        } // if
    } // if
    return true;
}

bool ratchet::component::enemy::EnemyComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::enemy::EnemyComponent::Clone(void) {
    return std::make_shared<ratchet::component::enemy::EnemyComponent>(*this);
}