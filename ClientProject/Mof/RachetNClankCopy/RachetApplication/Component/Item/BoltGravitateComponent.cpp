#include "BoltGravitateComponent.h"

#include "BoltComponent.h"
#include "../CharacterComponent.h"


my::BoltGravitateComponent::BoltGravitateComponent(int priority) :
    super(priority),
    _type_com() {
}

my::BoltGravitateComponent::BoltGravitateComponent(const BoltGravitateComponent& obj) :
    super(obj),
    _type_com() {
}

my::BoltGravitateComponent::~BoltGravitateComponent() {
}

std::string my::BoltGravitateComponent::GetType(void) const {
    return "BoltGravitateComponent";
}

std::string_view my::BoltGravitateComponent::GetStateType(void) const {
    return state::BoltActionType::kGravitate;
}

bool my::BoltGravitateComponent::Initialize(void) {
    super::Initialize();
    _type_com = super::GetOwner()->GetComponent<my::BoltComponent>();
    return true;
}

bool my::BoltGravitateComponent::Update(float delta_time) {
    if (auto type_com = _type_com.lock()) {
        if (auto player = type_com->GetPlayer(); player) {
            auto target_pos = player->GetPosition();
            target_pos.y += player->GetComponent<my::CharacterComponent>()->GetHeight();

            auto direction = Mof::CVector3(target_pos - super::GetOwner()->GetPosition());
            direction.Normal(direction);
            super::GetVelocityComponent()->AddVelocityForce(direction * 10.0f);
        } // if
    } // if
    return true;
}

bool my::BoltGravitateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BoltGravitateComponent::Clone(void) {
    return std::make_shared<my::BoltGravitateComponent>(*this);
}

bool my::BoltGravitateComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    velocity_com->SetGravity(0.0f);
    velocity_com->AddVelocityForce(Mof::CVector3(0.0f, 30.0f, 0.0f));
    return true;
}

bool my::BoltGravitateComponent::End(void) {
    super::End();
    return true;
}