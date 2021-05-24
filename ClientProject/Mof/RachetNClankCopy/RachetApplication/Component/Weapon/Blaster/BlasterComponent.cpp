#include "BlasterComponent.h"

#include "../../../Gamepad.h"
#include "../../../Actor/Weapon/Mechanical.h"


my::BlasterComponent::BlasterComponent(int priority) :
    super(priority) {
}

my::BlasterComponent::BlasterComponent(const BlasterComponent& obj) :
    super(obj) {
}

my::BlasterComponent::~BlasterComponent() {
}

std::string my::BlasterComponent::GetType(void) const {
    return "BlasterComponent";
}

bool my::BlasterComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool my::BlasterComponent::Update(float delta_time) {
    if (::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_B) || ::g_pInput->IsKeyHold(MOFKEY_SPACE)) {
        auto weapon = std::dynamic_pointer_cast<my::Mechanical> (super::GetOwner());
        if (weapon->CanFire()) {
            auto pos = super::GetOwner()->GetPosition();
            auto rotate = super::GetOwner()->GetRotate();
            //Mof::CVector3 pos;
            //mat.GetTranslation(pos);
            /*
            if (auto target = super::GetComponent<my::PlayerComponent>()->GetTarget().lock()) {
                auto target_pos = target->GetPosition();
                auto target_height = 0.5f;
                target_pos.y += target_height;
                weapon->SetLockOnPosition(target_pos);
            } // if
            else {
                weapon->ResetTargetPosition();
            } // else
            */
            weapon->Fire(def::Transform(pos, rotate));
        } // if
    } // if



    return true;
}

bool my::BlasterComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BlasterComponent::Clone(void) {
    return std::make_shared<my::BlasterComponent>(*this);
}