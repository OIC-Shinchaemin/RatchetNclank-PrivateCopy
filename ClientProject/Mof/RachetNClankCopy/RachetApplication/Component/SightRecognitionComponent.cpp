#include "SightRecognitionComponent.h"

#include <limits>

#include "My/Core/Math.h"
#include "Enemy/EnemyComponent.h"
#include "Player/PlayerComponent.h"
#include "Collision/Object/SightCollisionComponent.h"


void my::SightRecognitionComponent::RenderRay(const Mof::CRay3D& ray, float length, int color) {
    ::CGraphicsUtilities::RenderLine(ray.Position,
                                     ray.Position + ray.Direction * length,
                                     color);
}

void my::SightRecognitionComponent::RenderRay(Mof::Vector3 start, float degree_y) {
    auto ray = Mof::CRay3D(start);
    auto rotate = super::GetOwner()->GetRotate();
    rotate.y += math::ToRadian(degree_y);

    Mof::CMatrix44 mat;
    mat.RotationZXY(rotate);
    ray.Direction = -math::vec3::kUnitZ * mat;

    this->RenderRay(ray, this->GetRange(), def::color_rgba_u32::kGreen);
}

my::SightRecognitionComponent::SightRecognitionComponent(int priority) :
    super(priority),
    _range(5.0f),
    _player_com(),
    _enemy_com() {
    super::_active = true;
}

my::SightRecognitionComponent::SightRecognitionComponent(const SightRecognitionComponent& obj) :
    super(obj._priority),
    _range(obj._range),
    _player_com(),
    _enemy_com() {
    super::_active = true;
}

my::SightRecognitionComponent::~SightRecognitionComponent() {
}

std::string my::SightRecognitionComponent::GetType(void) const {
    return "SightRecognitionComponent";
}

float my::SightRecognitionComponent::GetRange(void) const {
    return this->_range;
}

const std::vector<std::weak_ptr<my::Actor>>& my::SightRecognitionComponent::GetRecognized(void) const {
    return this->_recognized;
}

bool my::SightRecognitionComponent::Initialize(void) {
    super::Initialize();
    if (auto tag = super::GetOwner()->GetTag(); tag == "Player") {
        _player_com = super::GetOwner()->GetComponent<my::PlayerComponent>();


        auto sight_coll = super::GetOwner()->GetComponent<my::SightCollisionComponent>();
        sight_coll->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Stay,
                                     "EnemyCollisionComponent",
                                     my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
            auto target = std::any_cast<std::shared_ptr<my::Actor>>(in.target);
            _recognized.push_back(target);
            return true;
        }));

    } // if
    else if (tag == "Enemy") {
        _enemy_com = super::GetOwner()->GetComponent<my::EnemyComponent>();

        auto sight_coll = super::GetOwner()->GetComponent<my::SightCollisionComponent>();
        sight_coll->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Stay,
                                     "PlayerCollisionComponent",
                                     my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
            auto target = std::any_cast<std::shared_ptr<my::Actor>>(in.target);
            _recognized.push_back(target);
            return true;
        }));


    } // else if


    return true;
}

bool my::SightRecognitionComponent::Update(float delta_time) {
    if (auto tag = super::GetOwner()->GetTag(); tag == "Player") {
        if (auto player_com = _player_com.lock()) {
            player_com->SetTarget(nullptr);
            if (!_recognized.empty()) {
                auto pos = super::GetOwner()->GetPosition();
                auto far_pos = math::vec3::kOne * std::numeric_limits<float>::max();
                auto it = std::min_element(_recognized.begin(), _recognized.end(), [pos, far_pos](std::weak_ptr<my::Actor>a, std::weak_ptr<my::Actor> b) {
                    auto a_pos = a.expired() ? far_pos : a.lock()->GetPosition();
                    auto b_pos = b.expired() ? far_pos : b.lock()->GetPosition();
                    return
                        Mof::CVector3Utilities::Distance(pos, a_pos) >
                        Mof::CVector3Utilities::Distance(pos, b_pos);
                });
                player_com->SetTarget(it->lock());
            } // if
        } // if
    } // if
    _recognized.clear();
    return true;
}

bool my::SightRecognitionComponent::Render(void) {
    // Ž‹ü•`‰æ

    Mof::Vector3 start = super::GetOwner()->GetPosition();
    std::weak_ptr<my::Actor> target_weak;
    float height = 0.0f;

    if (auto tag = super::GetOwner()->GetTag(); tag == "Player") {
        height = _player_com.lock()->GetHeight();
        target_weak = _player_com.lock()->GetTarget();
    } // if
    else if (tag == "Enemy") {
        height = _enemy_com.lock()->GetHeight();
        target_weak = _enemy_com.lock()->GetTarget();


    } // else if


    start.y += height;
    // Ž‹ŠE‹«ŠE•\Ž¦
    this->RenderRay(start, 0.0f);
    this->RenderRay(start, 90.0f);
    this->RenderRay(start, -90.0f);

    // ‘ÎÛ‚Ö‚ÌŽ‹ü‚ð•\Ž¦
    if (auto target = target_weak.lock()) {
        auto pos = target->GetPosition();
        pos.y += height;
        auto diff = pos - start;
        auto ray = Mof::CRay3D(start, diff);
        this->RenderRay(ray, Mof::CVector3Utilities::Length(diff), def::color_rgba_u32::kYellow);
    } // if
    return true;
}

std::shared_ptr<my::Component> my::SightRecognitionComponent::Clone(void) {
    return std::make_shared<my::SightRecognitionComponent>(*this);
}