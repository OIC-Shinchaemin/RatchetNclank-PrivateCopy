#include "SightRecognitionComponent.h"

#include <limits>

#include "Base/Core/Math.h"
#include "Enemy/EnemyComponent.h"
#include "Player/PlayerComponent.h"
#include "Collision/Object/SightCollisionComponent.h"
#include "../Actor/Character/Player.h"


void ratchet::component::SightRecognitionComponent::SenseEffectEmit(void) {
    if (!_effect_emitter) {
        _effect_emitter = _player_com.lock()->GetOwnerCastd()->GetEffectContainer()->CreateEmitter(effect::EffectType::PlayerSense);
    } // if


    auto info = ratchet::effect::Effect::Info();
    info.init_param.transform.position = super::GetOwner()->GetPosition();
    info.init_param.transform.position.y += _player_com.lock()->GetHeight() * 1.5f;
    info.init_param.color = def::color_rgba::kWhite;
    info.init_param.life_duration = 1.0f;
    _effect_emitter->Emit(info);

    /*
    auto camera_pos = CGraphicsUtilities::GetCamera()->GetViewPosition();
    auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Enemy>(super::GetOwner());
    auto target_pos = actor->GetPosition();
    auto pos = (owner->GetPosition() + target_pos) * 0.5f;
    auto diff = Mof::CVector3(camera_pos - pos);
    diff.Normal(diff);
    pos += diff * _player_com.lock()->GetVolume() * 2.0f;
    pos.y += _player_com.lock()->GetHeight();

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
    */
}

void ratchet::component::SightRecognitionComponent::RenderRay(const Mof::CRay3D& ray, float length, int color) {
    ::CGraphicsUtilities::RenderLine(ray.Position,
                                     ray.Position + ray.Direction * length,
                                     color);
}

void ratchet::component::SightRecognitionComponent::RenderRay(Mof::Vector3 start, float degree_y) {
    auto ray = Mof::CRay3D(start);
    auto rotate = super::GetOwner()->GetRotate();
    rotate.y += math::ToRadian(degree_y);

    Mof::CMatrix44 mat;
    mat.RotationZXY(rotate);
    ray.Direction = -math::vec3::kUnitZ * mat;

    this->RenderRay(ray, this->GetRange(), def::color_rgba_u32::kGreen);
}

ratchet::component::SightRecognitionComponent::SightRecognitionComponent(int priority) :
    super(priority),
    _range(0.0f),
    _player_com(),
    _ENEMY_com(),
    _effect_emitter(),
    _recognizing_count(0),
    _contact_enemy(false){
    super::Activate();
}

ratchet::component::SightRecognitionComponent::SightRecognitionComponent(const SightRecognitionComponent& obj) :
    super(obj),
    _range(obj._range),
    _player_com(),
    _ENEMY_com(),
    _recognizing_count(0),
    _contact_enemy(false) {
    super::Activate();
}

ratchet::component::SightRecognitionComponent::~SightRecognitionComponent() {
}

void ratchet::component::SightRecognitionComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* range = "range";

    _ASSERT_EXPR(param.HasMember(range), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[range].IsFloat(), L"パラメータの指定された型でありません");

    _range = param[range].GetFloat();
}

std::string ratchet::component::SightRecognitionComponent::GetType(void) const {
    return "SightRecognitionComponent";
}

float ratchet::component::SightRecognitionComponent::GetRange(void) const {
    return this->_range;
}

const std::vector<std::weak_ptr<ratchet::actor::Actor>>& ratchet::component::SightRecognitionComponent::GetRecognized(void) const {
    return this->_recognized;
}

bool ratchet::component::SightRecognitionComponent::Initialize(void) {
    super::Initialize();
    if (auto tag = super::GetOwner()->GetTag(); tag == "Player") {
        _player_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerComponent>();

        auto sight_coll = super::GetOwner()->GetComponent<ratchet::component::collision::SightCollisionComponent>();
        sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Stay,
                                     "EnemyCollisionComponent",
                                     ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
            //auto target = in.target.lock();
            //_recognized.push_back(target);
            return true;
        }));
        sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                                     "EnemyCollisionComponent",
                                     ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
            if (!_contact_enemy) {
                _contact_enemy = true;
                _contact_enemy_message_subject.Notify({});
            } // if

            if (_recognizing_count == 0) {
                this->SenseEffectEmit();
            } // if

            _recognizing_count++;
            auto target = in.target.lock();
            _recognized.push_back(target);
            return true;
        }));
        sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Exit,
                                     "EnemyCollisionComponent",
                                     ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {

            _recognizing_count--;
            _recognizing_count = std::clamp(_recognizing_count, 0, _recognizing_count);
            return true;
        }));

    } // if


    else if (tag == "Enemy") {
        _ENEMY_com = super::GetOwner()->GetComponent<ratchet::component::enemy::EnemyComponent>();

        auto sight_coll = super::GetOwner()->GetComponent<ratchet::component::collision::SightCollisionComponent>();
        sight_coll->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                                     "PlayerCollisionComponent",
                                     ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
            auto target = in.target.lock();
            _recognized.push_back(target);
            return true;
        }));
    } // else if
    return true;
}

bool ratchet::component::SightRecognitionComponent::Update(float delta_time) {

    if (auto tag = super::GetOwner()->GetTag(); tag == "Player") {
        if (auto player_com = _player_com.lock()) {
            player_com->SetTarget(nullptr);
            if (!_recognized.empty()) {
                auto pos = super::GetOwner()->GetPosition();
                auto far_pos = math::vec3::kOne * std::numeric_limits<float>::max();
                auto it = std::min_element(_recognized.begin(), _recognized.end(), [pos, far_pos](std::weak_ptr<ratchet::actor::Actor>a, std::weak_ptr<ratchet::actor::Actor> b) {
                    auto a_pos = a.expired() ? far_pos : a.lock()->GetPosition();
                    auto b_pos = b.expired() ? far_pos : b.lock()->GetPosition();
                    return
                        Mof::CVector3Utilities::Distance(pos, a_pos) <
                        Mof::CVector3Utilities::Distance(pos, b_pos);
                });
                player_com->SetTarget(it->lock());
            } // if
        } // if
    } // if
    _recognized.clear();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::SightRecognitionComponent::Clone(void) {
    return std::make_shared<ratchet::component::SightRecognitionComponent>(*this);
}