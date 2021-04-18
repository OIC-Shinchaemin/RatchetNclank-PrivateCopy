#include "PlayerInvincibleComponent.h"

#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../HpComponent.h"
#include "../Player/PlayerIdleComponent.h"


my::PlayerInvincibleComponent::PlayerInvincibleComponent(int priority) :
    super(priority),
    _invincible() {
}

my::PlayerInvincibleComponent::PlayerInvincibleComponent(const PlayerInvincibleComponent& obj) :
    super(obj._priority),
    _invincible() {
}

my::PlayerInvincibleComponent::~PlayerInvincibleComponent() {
}

std::string my::PlayerInvincibleComponent::GetType(void) const {
    return "PlayerInvincibleComponent";
}

bool my::PlayerInvincibleComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::PlayerInvincibleComponent::Update(float delta_time) {
    if (_invincible.Tick(delta_time)) {
        super::End();
    } // if
    return true;
}

bool my::PlayerInvincibleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerInvincibleComponent::Clone(void) {
    return std::make_shared<my::PlayerInvincibleComponent>(*this);
}

bool my::PlayerInvincibleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    _invincible.Initialize(1.0f, false);
    return true;
}