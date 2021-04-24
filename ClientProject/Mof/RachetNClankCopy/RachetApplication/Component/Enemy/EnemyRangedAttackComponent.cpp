#include "EnemyRangedAttackComponent.h"

#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "EnemyComponent.h"
#include "../../Actor/Bullet/EnemyBullet.h"
#include "../../Factory/FactoryManager.h"


my::EnemyRangedAttackComponent::EnemyRangedAttackComponent(int priority) :
    super(priority),
    _range(3.0f),
    _volume(0.2f),
    _shot_speed(3.0f),
    _motion_com(),
    _motion_state_com(),
    _enemy_com() {
}

my::EnemyRangedAttackComponent::EnemyRangedAttackComponent(const EnemyRangedAttackComponent& obj) :
    super(obj),
    _range(obj._range),
    _volume(obj._volume),
    _shot_speed(obj._shot_speed),
    _motion_com(),
    _motion_state_com(),
    _enemy_com() {
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
    _enemy_com = super::GetOwner()->GetComponent<my::EnemyComponent>();
    return true;
}

bool my::EnemyRangedAttackComponent::Update(float delta_time) {
    super::End();
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
    _ASSERT_EXPR(_enemy_com.lock()->GetTargetPosition().has_value(), L"“G‚ð”FŽ¯‚µ‚Ä‚¢‚Ü‚¹‚ñ");
    auto enemy_com = _enemy_com.lock();

    auto param = my::Bullet::Param();
    auto owner = super::GetOwner();
    auto transform = my::Transform();
    param.transform.position = owner->GetPosition();
    param.transform.position.y += enemy_com->GetHeight();
    param.transform.rotate = owner->GetRotate();

    Mof::CVector3 direction = enemy_com->GetTargetPosition().value() - param.transform.position;
    direction.Normal(direction);
    param.speed = direction * _shot_speed;

    auto add = my::FactoryManager::Singleton().CreateActor<my::EnemyBullet>("../Resource/builder/enemy_bullet.json", &param);
    add->Start(param);
    super::GetOwner()->Notify("AddRequest", add);

    return true;
}