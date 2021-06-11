#include "SightRecognitionComponent.h"

#include <limits>

#include "Base/Core/Math.h"
#include "Enemy/EnemyComponent.h"
#include "Player/PlayerComponent.h"
#include "Collision/Object/SightCollisionComponent.h"


void rachet::SightRecognitionComponent::RenderRay(const Mof::CRay3D& ray, float length, int color) {
    ::CGraphicsUtilities::RenderLine(ray.Position,
                                     ray.Position + ray.Direction * length,
                                     color);
}

void rachet::SightRecognitionComponent::RenderRay(Mof::Vector3 start, float degree_y) {
    auto ray = Mof::CRay3D(start);
    auto rotate = super::GetOwner()->GetRotate();
    rotate.y += math::ToRadian(degree_y);

    Mof::CMatrix44 mat;
    mat.RotationZXY(rotate);
    ray.Direction = -math::vec3::kUnitZ * mat;

    this->RenderRay(ray, this->GetRange(), def::color_rgba_u32::kGreen);
}

rachet::SightRecognitionComponent::SightRecognitionComponent(int priority) :
    super(priority),
    _range(0.0f),
    _player_com(),
    _ENEMY_com() {
    super::Activate();
}

rachet::SightRecognitionComponent::SightRecognitionComponent(const SightRecognitionComponent& obj) :
    super(obj),
    _range(obj._range),
    _player_com(),
    _ENEMY_com() {
    super::Activate();
}

rachet::SightRecognitionComponent::~SightRecognitionComponent() {
}

void rachet::SightRecognitionComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* range = "range";

    _ASSERT_EXPR(param.HasMember(range), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[range].IsFloat(), L"パラメータの指定された型でありません");

    _range = param[range].GetFloat();
}

std::string rachet::SightRecognitionComponent::GetType(void) const {
    return "SightRecognitionComponent";
}

float rachet::SightRecognitionComponent::GetRange(void) const {
    return this->_range;
}

const std::vector<std::weak_ptr<rachet::Actor>>& rachet::SightRecognitionComponent::GetRecognized(void) const {
    return this->_recognized;
}

bool rachet::SightRecognitionComponent::Initialize(void) {
    super::Initialize();
    if (auto tag = super::GetOwner()->GetTag(); tag == "Player") {
        _player_com = super::GetOwner()->GetComponent<rachet::PlayerComponent>();


        auto sight_coll = super::GetOwner()->GetComponent<rachet::SightCollisionComponent>();
        sight_coll->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Stay,
                                     "EnemyCollisionComponent",
                                     rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
            auto target = in.target.lock();
            _recognized.push_back(target);
            return true;
        }));
    } // if
    else if (tag == "Enemy") {
        _ENEMY_com = super::GetOwner()->GetComponent<rachet::EnemyComponent>();

        auto sight_coll = super::GetOwner()->GetComponent<rachet::SightCollisionComponent>();
        sight_coll->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Stay,
                                     "PlayerCollisionComponent",
                                     rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
            auto target = in.target.lock();
            _recognized.push_back(target);
            return true;
        }));
    } // else if
    return true;
}

bool rachet::SightRecognitionComponent::Update(float delta_time) {

    if (auto tag = super::GetOwner()->GetTag(); tag == "Player") {
        if (auto player_com = _player_com.lock()) {
            player_com->SetTarget(nullptr);
            if (!_recognized.empty()) {
                auto pos = super::GetOwner()->GetPosition();
                auto far_pos = math::vec3::kOne * std::numeric_limits<float>::max();
                auto it = std::min_element(_recognized.begin(), _recognized.end(), [pos, far_pos](std::weak_ptr<rachet::Actor>a, std::weak_ptr<rachet::Actor> b) {
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

std::shared_ptr<rachet::Component> rachet::SightRecognitionComponent::Clone(void) {
    return std::make_shared<rachet::SightRecognitionComponent>(*this);
}