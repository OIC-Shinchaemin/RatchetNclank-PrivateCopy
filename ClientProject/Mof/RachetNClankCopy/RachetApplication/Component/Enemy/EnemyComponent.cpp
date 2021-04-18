#include "EnemyComponent.h"

#include "../../Gamepad.h"
#include "../Collision/Object/EnemyCollisionObject.h"


my::EnemyComponent::EnemyComponent(int priority) :
    super(priority),
    _volume(0.5f),
    _height(1.0f) {
}

my::EnemyComponent::EnemyComponent(const EnemyComponent& obj) :
    super(obj),
    _volume(obj._volume),
    _height(obj._height) {
}

my::EnemyComponent::~EnemyComponent() {
}


std::string my::EnemyComponent::GetType(void) const {
    return "EnemyComponent";
}

float my::EnemyComponent::GetVolume(void) const {
    return this->_volume;
}

float my::EnemyComponent::GetHeight(void) const {
    return this->_height;
}

bool my::EnemyComponent::Initialize(void) {
    super::Initialize();
    super::Start();
    return true;
}

bool my::EnemyComponent::Update(float delta_time) {
    return true;
}

bool my::EnemyComponent::Render(void) {
    auto coll_com = super::GetOwner()->GetComponent<my::EnemyCollisionObject>();
    if (coll_com->GetSphere().has_value()) {
        ::CGraphicsUtilities::RenderLineSphere(coll_com->GetSphere().value(), def::color_rgba::kCyan);
    } // if
    return true;
}

bool my::EnemyComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyComponent::Clone(void) {
    return std::make_shared<my::EnemyComponent>(*this);
}