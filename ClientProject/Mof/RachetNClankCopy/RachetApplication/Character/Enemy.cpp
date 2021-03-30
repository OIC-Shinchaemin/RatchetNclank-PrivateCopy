#include "Enemy.h"


Mof::CVector3 my::Enemy::UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity) {
    float sleep_threshold = 0.01f;
    if (sleep_threshold < velocity.Length()) {
        rotate += velocity * delta_time;
    } // if

    if (math::kTwoPi <= rotate.y) {
        rotate.y -= math::kTwoPi;
    } // if
    else if (rotate.y <= 0.0f) {
        rotate.y += math::kTwoPi;
    } // else if
    return rotate;
}

Mof::CVector3 my::Enemy::UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity) {
    float sleep_threshold = 0.001f;

    if (sleep_threshold < velocity.Length()) {
        position += velocity * delta_time;
    } // if
    return position;
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
    _state(my::AIState::Patrol){
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
    if (auto target = _target.lock()) {
        auto dir = target->GetPosition() - super::GetPosition();
        float speed = 0.3f;
        auto accele = dir * speed;
        _velocity.AddVelocityForce(accele);
    } // if
    return true;
}

bool my::Enemy::Update(float delta_time) {
    super::Update(delta_time);
    _velocity.Update(delta_time);

    auto owner = this;
    // rotate
    auto rotate = this->UpdateRotate(delta_time, owner->GetRotate(), _velocity.GetAngularVelocity());
    owner->SetRotate(rotate);
    // position
    auto pos = this->UpdatePosition(delta_time, owner->GetPosition(), _velocity.GetVelocity());
    //owner->SetPosition(pos);

    if (pos.y < 0.0f) {
        pos.y = 0.0f;
    } // if
    owner->SetPosition(pos);

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

my::Velocity::Velocity() :
    _velocity(),
    _angular_velocity(),
    _velocity_force(),
    _angular_velocity_force(),
    _gravity(0.25f),
    _drag(0.8f),
    _angular_drag(0.8f) {
}

my::Velocity::~Velocity() {
}

Mof::CVector3 my::Velocity::GetVelocity(void) const {
    return this->_velocity;
}

Mof::CVector3 my::Velocity::GetAngularVelocity(void) const {
    return this->_angular_velocity;
}

Mof::CVector3 my::Velocity::GetVelocityForce(void) const {
    return this->_velocity_force;
}

void my::Velocity::AddVelocityForce(Mof::CVector3 accele) {
    this->_velocity_force += accele;
}

void my::Velocity::AddAngularVelocityForce(Mof::CVector3 accele) {
    this->_angular_velocity_force += accele;
}

bool my::Velocity::Update(float delta_time) {
    _angular_velocity += _angular_velocity_force;
    _velocity += _velocity_force;

    _velocity.y -= _gravity;
    _velocity *= _drag;
    _angular_velocity *= _angular_drag;

    //_prev_velocity_force = _velocity_force;
    _velocity_force = Mof::CVector3();
    _angular_velocity_force = Mof::CVector3();
    return true;
}