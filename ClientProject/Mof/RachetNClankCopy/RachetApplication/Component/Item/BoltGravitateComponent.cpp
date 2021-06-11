#include "BoltGravitateComponent.h"

#include "BoltComponent.h"
#include "../CharacterComponent.h"


rachet::BoltGravitateComponent::BoltGravitateComponent(int priority) :
    super(priority),
    _type_com() {
}

rachet::BoltGravitateComponent::BoltGravitateComponent(const BoltGravitateComponent& obj) :
    super(obj),
    _type_com() {
}

rachet::BoltGravitateComponent::~BoltGravitateComponent() {
}

std::string rachet::BoltGravitateComponent::GetType(void) const {
    return "BoltGravitateComponent";
}

std::string_view rachet::BoltGravitateComponent::GetStateType(void) const {
    return state::BoltActionType::kGravitate;
}

bool rachet::BoltGravitateComponent::Initialize(void) {
    super::Initialize();
    _type_com = super::GetOwner()->GetComponent<rachet::BoltComponent>();
    return true;
}

bool rachet::BoltGravitateComponent::Update(float delta_time) {
    if (auto type_com = _type_com.lock()) {
        if (auto player = type_com->GetPlayer(); player) {
            auto target_pos = player->GetPosition();
            target_pos.y += player->GetComponent<rachet::CharacterComponent>()->GetHeight();

            auto direction = Mof::CVector3(target_pos - super::GetOwner()->GetPosition());
            direction.Normal(direction);
            super::GetVelocityComponent()->AddVelocityForce(direction * 10.0f);
        } // if
    } // if
    return true;
}

bool rachet::BoltGravitateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BoltGravitateComponent::Clone(void) {
    return std::make_shared<rachet::BoltGravitateComponent>(*this);
}

bool rachet::BoltGravitateComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    velocity_com->SetGravity(0.0f);
    velocity_com->AddVelocityForce(Mof::CVector3(0.0f, 30.0f, 0.0f));
    return true;
}

bool rachet::BoltGravitateComponent::End(void) {
    super::End();
    return true;
}