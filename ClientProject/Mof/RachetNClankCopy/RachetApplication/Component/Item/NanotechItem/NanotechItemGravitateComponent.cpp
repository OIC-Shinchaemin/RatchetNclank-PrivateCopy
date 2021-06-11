#include "NanotechItemGravitateComponent.h"

#include "NanotechItemComponent.h"
#include "../../CharacterComponent.h"


rachet::NanotechItemGravitateComponent::NanotechItemGravitateComponent(int priority) :
    super(priority),
    _type_com() {
}

rachet::NanotechItemGravitateComponent::NanotechItemGravitateComponent(const NanotechItemGravitateComponent& obj) :
    super(obj),
    _type_com() {
}

rachet::NanotechItemGravitateComponent::~NanotechItemGravitateComponent() {
}

std::string rachet::NanotechItemGravitateComponent::GetType(void) const {
    return "NanotechItemGravitateComponent";
}

std::string_view rachet::NanotechItemGravitateComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kGravitate;
}

bool rachet::NanotechItemGravitateComponent::Initialize(void) {
    super::Initialize();
    _type_com = super::GetOwner()->GetComponent<rachet::NanotechItemComponent>();
    return true;
}

bool rachet::NanotechItemGravitateComponent::Update(float delta_time) {
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

bool rachet::NanotechItemGravitateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::NanotechItemGravitateComponent::Clone(void) {
    return std::make_shared<rachet::NanotechItemGravitateComponent>(*this);
}

bool rachet::NanotechItemGravitateComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    velocity_com->SetGravity(0.0f);
    velocity_com->AddVelocityForce(Mof::CVector3(0.0f, 30.0f, 0.0f));
    return true;
}

bool rachet::NanotechItemGravitateComponent::End(void) {
    super::End();
    return true;
}