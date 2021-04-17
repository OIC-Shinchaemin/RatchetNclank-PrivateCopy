#include "SightRecognitionComponent.h"

#include "My/Core/Math.h"
#include "../Actor/Character/Enemy.h"
#include "Enemy/EnemyComponent.h"


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
    _enemy_com() {
    super::_active = true;
}

my::SightRecognitionComponent::SightRecognitionComponent(const SightRecognitionComponent& obj) :
    super(obj._priority),
    _range(obj._range),
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

bool my::SightRecognitionComponent::Initialize(void) {
    super::Initialize();
    _enemy_com = super::GetOwner()->GetComponent<my::EnemyComponent>();
    return true;
}

bool my::SightRecognitionComponent::ContainInRecognitionRange(Mof::CVector3 target) {
    // ëäéËÇ÷ÇÃÉxÉNÉgÉãÇ∆é©ï™ÇÃëOï˚ÉxÉNÉgÉãÇÃì‡êœÇ™ê≥Åi>ÇOÅjÇÃèÍçáÇÕâsäpÇ≈Ç†ÇËëOï˚ÇXÇOÅãà»ì‡Ç∆îªífÇ≈Ç´ÇÈ
    auto pos = super::GetOwner()->GetPosition();
    auto rotate = super::GetOwner()->GetRotate();

    if (!Mof::CSphere(pos, _range).CollisionPoint(target)) {
        return false;
    } // if


    Mof::CVector3 dir = target - pos;
    Mof::CVector3 front(-math::vec3::kUnitZ);
    Mof::CMatrix33 mat;
    mat.RotationZXY(rotate);
    front *= mat;
    if (front.Dot(dir) > 0.0f) {
        return true;
        /* è·äQï®ñ≥Ç¢Ç»ÇÁå©Ç¶ÇÈÇ‡ÇÃÇ∆Ç∑ÇÈ
        _recognition.push_back(candidate);
        */
    } // if
    return false;
}

bool my::SightRecognitionComponent::Render(void) {
    auto enemy = std::dynamic_pointer_cast<my::Enemy>(super::GetOwner());
    // éãê¸ï`âÊ

    Mof::Vector3 start = super::GetOwner()->GetPosition();
    float height = _enemy_com.lock()->GetHeight();
    start.y += height;

    // éãäEã´äEï\é¶
    this->RenderRay(start, 0.0f);
    this->RenderRay(start, 90.0f);
    this->RenderRay(start, -90.0f);

    // ëŒè€Ç÷ÇÃéãê¸Çï\é¶
    if (auto target = enemy->GetTarget().lock()) {
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