#include "PlayerComponent.h"

#include "../Player/PlayerIdleComponent.h"
#include "../Player/PlayerMoveComponent.h"


my::PlayerComponent::PlayerComponent(int priority) :
    super(priority),
    _idle_com(),
    _move_com() {
}

my::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _idle_com(),
    _move_com() {
}

my::PlayerComponent::~PlayerComponent() {
}


std::string my::PlayerComponent::GetType(void) const {
    return "PlayerComponent";
}

bool my::PlayerComponent::Initialize(void) {
    super::Initialize();

    _idle_com = super::GetOwner()->GetComponent<my::PlayerIdleComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();

    return true;
}

bool my::PlayerComponent::Update(float delta_time) {
    return true;
}

bool my::PlayerComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerComponent::Clone(void) {
    return std::make_shared<my::PlayerComponent>(*this);
}