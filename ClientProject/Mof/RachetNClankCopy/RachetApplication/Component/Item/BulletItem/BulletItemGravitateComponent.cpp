#include "BulletItemGravitateComponent.h"

#include "BulletItemComponent.h"
#include "../../CharacterComponent.h"


my::BulletItemGravitateComponent::BulletItemGravitateComponent(int priority) :
    super(priority),
    _type_com() {
}

my::BulletItemGravitateComponent::BulletItemGravitateComponent(const BulletItemGravitateComponent& obj) :
    super(obj),
    _type_com() {
}

my::BulletItemGravitateComponent::~BulletItemGravitateComponent() {
}

std::string my::BulletItemGravitateComponent::GetType(void) const {
    return "BulletItemGravitateComponent";
}

std::string_view my::BulletItemGravitateComponent::GetStateType(void) const {
    return state::BulletItemActionType::kGravitate;
}

bool my::BulletItemGravitateComponent::Initialize(void) {
    super::Initialize();
    _type_com = super::GetOwner()->GetComponent<my::BulletItemComponent>();
    return true;
}

bool my::BulletItemGravitateComponent::Update(float delta_time) {
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

bool my::BulletItemGravitateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BulletItemGravitateComponent::Clone(void) {
    return std::make_shared<my::BulletItemGravitateComponent>(*this);
}

bool my::BulletItemGravitateComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    velocity_com->SetGravity(0.0f);
    velocity_com->AddVelocityForce(Mof::CVector3(0.0f, 30.0f, 0.0f));
    return true;
}

bool my::BulletItemGravitateComponent::End(void) {
    super::End();
    return true;
}