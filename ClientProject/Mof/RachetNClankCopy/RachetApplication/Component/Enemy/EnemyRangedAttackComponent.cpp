#include "EnemyRangedAttackComponent.h"

#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../../Actor/Bullet/EnemyBullet.h"
#include "../../Factory/FactoryManager.h"


my::EnemyRangedAttackComponent::EnemyRangedAttackComponent(int priority) :
    super(priority),
    _range(3.0f),
    _volume(0.5f),
    _motion_com(),
    _motion_state_com() {
}

my::EnemyRangedAttackComponent::EnemyRangedAttackComponent(const EnemyRangedAttackComponent& obj) :
    super(obj),
    _range(obj._range),
    _volume(obj._volume),
    _motion_com(),
    _motion_state_com() {
}

my::EnemyRangedAttackComponent ::~EnemyRangedAttackComponent() {
}

std::string my::EnemyRangedAttackComponent::GetType(void) const {
    return "EnemyRangedAttackComponent";
}

float my::EnemyRangedAttackComponent::GetRange(void) const {
    return this->_range;
}

float my::EnemyRangedAttackComponent::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere my::EnemyRangedAttackComponent::GetCanAttackRangeSphere(void) const {
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _range);
}

bool my::EnemyRangedAttackComponent::Initialize(void) {
    super::Initialize();

    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();

    return true;
}

bool my::EnemyRangedAttackComponent::Update(float delta_time) {
    if (auto motion_com = _motion_com.lock()) {
        if (motion_com->IsEndMotion()) {
            super::End();
        } // if
    } // if
    return true;
}

bool my::EnemyRangedAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyRangedAttackComponent::Clone(void) {
    return std::make_shared<my::EnemyRangedAttackComponent>(*this);
}

bool my::EnemyRangedAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionAttackState");
    } // if

    auto param = my::Bullet::Param();
    auto owner = super::GetOwner();
    auto transform = my::Transform();
    param.transform.position = owner->GetPosition();
    param.transform.rotate = owner->GetRotate();
    
    float shot_speed = 6.0f;
    auto speed = Mof::CVector3(0.0f, 0.0f, -shot_speed);
    speed.RotateAround(math::vec3::kZero, param.transform.rotate);
    param.speed = speed;
    param.speed.y = shot_speed * 0.2f;

    auto add = my::FactoryManager::Singleton().CreateActor<my::EnemyBullet>("../Resource/builder/enemy_bullet.json", &param);
    add->Start(param);
    super::GetOwner()->Notify("AddRequest", add);

    return true;
}