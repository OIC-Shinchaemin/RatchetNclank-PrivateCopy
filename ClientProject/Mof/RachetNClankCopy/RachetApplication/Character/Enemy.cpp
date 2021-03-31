#include "Enemy.h"


void my::Enemy::InputMoveVelocity(Mof::CVector2 stick, float speed) {
    // “ü—Í‘¬“x
    auto accele = Mof::CVector3(0.0f, 0.0f, -speed * stick.Length());
    auto rotate = super::GetRotate();
    accele.RotateAround(Mof::CVector3(), rotate);

    // ‘¬“x’Ç‰Á
    super::_velocity.AddVelocityForce(accele);
}

void my::Enemy::InputMoveAngularVelocity(Mof::CVector2 stick, float speed) {
    // “ü—ÍŠp“x
    auto rotate = super::GetRotate();

    float angle_y = std::atan2(-stick.y, stick.x) - math::kHalfPi;

    if (math::kTwoPi <= angle_y) {
        angle_y -= math::kTwoPi;
    } // if
    else if (angle_y <= 0.0f) {
        angle_y += math::kTwoPi;
    } // else if

    // ·•ªŠp“x
    angle_y -= rotate.y;
    if (math::kPi < angle_y) {
        angle_y -= math::kTwoPi;
    } // if
    else if (angle_y < -math::kPi) {
        angle_y += math::kTwoPi;
    } // else if

    auto accele = Mof::CVector3(0.0f, angle_y * speed, 0.0f);
    super::_velocity.AddAngularVelocityForce(accele);
}

void my::Enemy::RenderRay(const Mof::CRay3D& ray, float length, int color) {
    ::CGraphicsUtilities::RenderLine(ray.Position,
                                     ray.Position + ray.Direction * length,
                                     color);
}

void my::Enemy::RenderRay(Mof::Vector3 start, float degree_y) {
    auto ray = Mof::CRay3D(start);
    auto rotate = super::GetRotate();
    rotate.y += math::ToRadian(degree_y);

    Mof::CMatrix44 mat;
    mat.RotationZXY(rotate);
    ray.Direction = -math::vec3::kUnitZ * mat;

    this->RenderRay(ray, _sight.GetRange(), def::color_rgba_u32::kGreen);
}

my::Enemy::Enemy() :
    super(),
    _state(my::AIState::Patrol) {
    //super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/enemy/catcatup.mom");
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/Chara/Chr_01_ion_mdl_01.mom");
    float scale = 0.2f;
    super::SetScale(Mof::CVector3(scale, scale, scale));
}

my::Enemy::~Enemy() {
}

void my::Enemy::SetTarget(const std::shared_ptr<my::Character>& ptr) {
    this->_target = ptr;
}

bool my::Enemy::Initialize(const def::Transform& transform) {
    super::Initialize(transform);
    _sight.SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));


    if (auto mesh = _mesh.lock()) {
        _motion = mesh->CreateMotionController();
        _motion->ChangeMotion(0);
    } // if

    return true;
}

bool my::Enemy::Input(void) {
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    if (_state == my::AIState::Patrol) {
        in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, 3.14f * 2.0f));

        float angular_speed = 5.0f;
        float speed = 0.1f;
        this->InputMoveAngularVelocity(in, angular_speed);
        this->InputMoveVelocity(in, speed);
    } // if
    else if (_state == my::AIState::Combat) {

        if (auto target = _target.lock()) {
            auto dir = target->GetPosition() - super::GetPosition();
            float angle = std::atan2(dir.z, dir.x);
            in = math::Rotate(in.x, in.y, angle);

            float angular_speed = 1.0f;
            float speed = 0.1f;
            this->InputMoveAngularVelocity(in, angular_speed);
            this->InputMoveVelocity(in, speed);
        } // if

    } // else if


    return true;
}

bool my::Enemy::Update(float delta_time) {
    super::Update(delta_time);
    super::UpdateTransform(delta_time);
    return true;
}

bool my::Enemy::Render(void) {
    super::Render();
    return true;
}

bool my::Enemy::ContainInRecognitionRange(Mof::CVector3 pos) {
    return _sight.ContainInRecognitionRange(pos);
}

void my::Enemy::RenderDebug(void) {
    super::RenderDebug();

    // Ž‹ü•`‰æ
    Mof::Vector3 start = super::GetPosition();
    float h = super::_height;
    start.y += h;

    // Ž‹ŠE‹«ŠE•\Ž¦
    this->RenderRay(start, 0.0f);
    this->RenderRay(start, 90.0f);
    this->RenderRay(start, -90.0f);

    // ‘ÎÛ‚Ö‚ÌŽ‹ü‚ð•\Ž¦
    if (auto target = _target.lock()) {
        auto pos = target->GetPosition();
        pos.y += super::_height;
        auto diff = pos - start;
        auto ray = Mof::CRay3D(start, diff);
        this->RenderRay(ray, Mof::CVector3Utilities::Length(diff), def::color_rgba_u32::kYellow);
    } // if
}