#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MeshComponent.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"
#include "../../Factory/FactoryManager.h"
#include "../../Factory/ActorFactory.h"


void my::Player::End(void) {
    Observable::Notify("PlayerDead", shared_from_this());
}

bool my::Player::Disable(void) {
    this->_enable = false;    
    return true;
}

bool my::Player::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::Player::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    _enable = true;

    _player_com = super::GetComponent<my::PlayerComponent>();
    return true;
}

my::Player::Player() :
    _current_mechanical(),
    _enable(true) {
    super::SetTag("Player");

    auto param = super::Param();
    param.name = "weapon";
    param.tag = "omni_wrench";
    _omniwrench = my::FactoryManager::Singleton().CreateActor<my::OmniWrench>("builder/omni_wrench.json", &param);
}

my::Player::~Player() {
}

void my::Player::OnNotify(std::shared_ptr<my::Mechanical> change) {
    _current_mechanical = change;
}

void my::Player::OnNotify(const my::QuickChangeSystem::Info& info) {
    if (info.color.a <= 0.0f) {
        if (auto player_com = _player_com.lock()) {
            player_com->EnableAction();
        } // if
    } // if
    else if (info.color.a >= 1.0f) {
        if (auto player_com = _player_com.lock()) {
            player_com->DisableAction();
        } // if
    } // else if
}

bool my::Player::Update(float delta_time) {
    if (!_enable) {
        return false;
    } // if

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
    if (!_enable) {
        return false;
    } // if
    super::Render();

    // •Ší‚ğİ’è‚·‚éƒ{[ƒ“‚Ìî•ñ‚ğæ“¾‚·‚é
    auto motion = super::GetComponent<my::MotionComponent>()->GetMotionData();
    LPBONEMOTIONSTATE bone_state = motion->GetBoneState("UPP_weapon");
    Mof::CMatrix44 mat = bone_state->pBone->GetRotationOffsetMatrix() * bone_state->BoneMatrix;
    if (auto weapon = _current_mechanical.lock()) {
        weapon->Render(mat);
    } // if
    else {
        if (auto mesh = _omniwrench->GetComponent<my::MeshComponent>()) {
            mesh->GetMesh().lock()->Render(mat);
        } // if
    } // else
    return true;
}

bool my::Player::Release(void) {
    super::Release();
    _current_mechanical.reset();
    return true;
}