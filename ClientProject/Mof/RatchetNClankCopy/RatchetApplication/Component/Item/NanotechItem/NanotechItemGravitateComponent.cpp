#include "NanotechItemGravitateComponent.h"

#include "NanotechItemComponent.h"
#include "../../CharacterComponent.h"


ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::NanotechItemGravitateComponent(int priority) :
    super(priority),
    _type_com() {
}

ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::NanotechItemGravitateComponent(const NanotechItemGravitateComponent& obj) :
    super(obj),
    _type_com() {
}

ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::~NanotechItemGravitateComponent() {
}

std::string ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::GetType(void) const {
    return "NanotechItemGravitateComponent";
}

std::string_view ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kGravitate;
}

bool ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::Initialize(void) {
    super::Initialize();
    _type_com = super::GetOwner()->GetComponent<ratchet::component::item::nanotechitem::NanotechItemComponent>();
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::Update(float delta_time) {
    if (auto type_com = _type_com.lock()) {
        if (auto player = type_com->GetPlayer(); player) {
            auto target_pos = player->GetPosition();
            target_pos.y += player->GetComponent<ratchet::component::CharacterComponent>()->GetHeight();

            auto direction = Mof::CVector3(target_pos - super::GetOwner()->GetPosition());
            direction.Normal(direction);
            super::GetVelocityComponent()->AddVelocityForce(direction * 10.0f);
        } // if
    } // if
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::nanotechitem::NanotechItemGravitateComponent>(*this);
}

bool ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    velocity_com->SetGravity(0.0f);
    velocity_com->AddVelocityForce(Mof::CVector3(0.0f, 30.0f, 0.0f));
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemGravitateComponent::End(void) {
    super::End();
    return true;
}