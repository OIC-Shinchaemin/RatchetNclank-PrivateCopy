#include "Player.h"

#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"


my::Player::Player() :
    _current_mechanical() {
    super::SetTag("Player");
}

my::Player::~Player() {
}

void my::Player::OnNotify(std::shared_ptr<my::Mechanical> change) {
    _current_mechanical = change;
}

bool my::Player::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    return true;
}

bool my::Player::Update(float delta_time) {
    super::Update(delta_time);

    if (auto weapon = _current_mechanical.lock()) {
        if (weapon->IsAction() && weapon->CanFire()) {
            auto pos = super::GetPosition();
            auto height = super::GetComponent<my::PlayerComponent>()->GetHeight();
            pos.y += height;
            weapon->Fire(def::Transform(pos, super::GetRotate()));
        } // if
    } // if

    // update child
    if (auto weapon = _current_mechanical.lock()) {
        weapon->Update(delta_time);
    } // if
    return true;
}

bool my::Player::Render(void) {
    super::Render();

    // •Ší‚ğİ’è‚·‚éƒ{[ƒ“‚Ìî•ñ‚ğæ“¾‚·‚é
    auto motion = super::GetComponent<my::MotionComponent>()->GetMotionData();
    LPBONEMOTIONSTATE pBoneState = motion->GetBoneState("UPP_weapon");
    if (auto weapon = _current_mechanical.lock()) {
        // weapon ->Render(pBoneState);
        weapon->Render();
        auto name = weapon->GetName();
        ::CGraphicsUtilities::RenderString(600.0f, 300.0f, name.c_str());
    } // if
    return true;
}

bool my::Player::Release(void) {
    super::Release();
    _current_mechanical.reset();
    return true;
}