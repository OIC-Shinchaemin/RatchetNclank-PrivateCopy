#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"


void my::Player::End(void) {
    Observable::Notify("PlayerDead", shared_from_this());
}

my::Player::Player() :
    _current_mechanical() {
    super::SetTag("Player");
}

my::Player::~Player() {
}

void my::Player::OnNotify(std::shared_ptr<my::Mechanical> change) {
    _current_mechanical = change;
}

bool my::Player::Update(float delta_time) {
    super::Update(delta_time);
    if (auto weapon = _current_mechanical.lock()) {
        weapon->Update(delta_time);
        if (weapon->IsAction() && weapon->CanFire()) {
            auto pos = super::GetPosition();
            auto height = super::GetComponent<my::PlayerComponent>()->GetHeight();
            pos.y += height;
            if (auto target = super::GetComponent<my::PlayerComponent>()->GetTarget().lock()) {
                auto target_pos = target->GetPosition();
                target_pos.y += height;
                weapon->SetLockOnPosition(target_pos);
            } // if
            else {
                weapon->ResetTargetPosition();
            } // else

            weapon->Fire(def::Transform(pos, super::GetRotate()));
        } // if
    } // if
    return true;
}

bool my::Player::Render(void) {
    super::Render();
    return true;

    /*
    // 武器を設定するボーンの情報を取得する
    auto motion = super::GetComponent<my::MotionComponent>()->GetMotionData();
    LPBONEMOTIONSTATE pBoneState = motion->GetBoneState("UPP_weapon");
    if (auto weapon = _current_mechanical.lock()) {
        // weapon ->Render(pBoneState);
        weapon->Render();
        auto name = weapon->GetName();
        ::CGraphicsUtilities::RenderString(600.0f, 300.0f, name.c_str());
    } // if
    */
    return true;
}

bool my::Player::Release(void) {
    super::Release();
    _current_mechanical.reset();
    return true;
}