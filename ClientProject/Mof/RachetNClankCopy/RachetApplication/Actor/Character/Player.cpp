#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MeshComponent.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"
#include "../../Factory/FactoryManager.h"
#include "../../Factory/ActorFactory.h"


std::shared_ptr<my::Actor> my::Player::GetChild(const std::string& tag) const {
    auto it = std::find_if(_children.begin(), _children.end(), [&tag](const std::shared_ptr<my::Actor>& ptr) {
        return ptr->GetTag() == tag;
                           });
    if (it == _children.end()) {
        return nullptr;
    } // if
    return *it;
}

void my::Player::End(void) {
    Observable::Notify("PlayerDead", shared_from_this());
}

bool my::Player::Disable(void) {
    this->_enable = false;
    return true;
}

void my::Player::AddChild(const std::shared_ptr<my::Actor>& ptr) {
    this->_children.push_back(ptr);
}

bool my::Player::Initialize(void) {
    this->Initialize();
    return true;
}

bool my::Player::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    _enable = true;

    _player_com = super::GetComponent<my::PlayerComponent>();
    if (auto motion_com = super::GetComponent<my::MotionComponent>(); motion_com) {
        auto motion = motion_com->GetMotionData();
        _upp_bone_state = motion->GetBoneState("UPP_weapon");
    } // if
    return true;
}

my::Player::Player() :
    _current_mechanical(),
    _enable(true) {
    super::SetTag("Player");
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

    // •Ší‚ðÝ’è‚·‚éƒ{[ƒ“‚Ìî•ñ‚ðŽæ“¾‚·‚é
    Mof::CMatrix44 mat = _upp_bone_state->pBone->GetRotationOffsetMatrix() * _upp_bone_state->BoneMatrix;

    if (auto weapon = _current_mechanical.lock()) {
        weapon->Update(delta_time);
        if (weapon->IsAction() && weapon->CanFire()) {
            Mof::CVector3 pos;
            mat.GetTranslation(pos);

            if (auto target = super::GetComponent<my::PlayerComponent>()->GetTarget().lock()) {
                auto target_pos = target->GetPosition();
                auto target_height = 1.0f;
                target_pos.y += target_height;
                weapon->SetLockOnPosition(target_pos);
            } // if
            else {
                weapon->ResetTargetPosition();
            } // else
            weapon->Fire(def::Transform(pos, super::GetRotate()));
        } // if
    } // if

    for (auto actor : _children) {
        //actor->SetParentTransform(mat);
        Mof::CVector3 scale, rotate, translate;

        mat.GetScaling(scale);
        mat.GetRotation(rotate);
        mat.GetTranslation(translate);
        actor->SetScale(scale);
        actor->SetPosition(translate);
        actor->SetRotate(rotate);
    } // for
    return true;
}

bool my::Player::Render(void) {
    if (!_enable) {
        return false;
    } // if
    super::Render();

    //_omniwrench->Render();
    return true;
}

bool my::Player::Release(void) {
    super::Release();
    _children.clear();
    _current_mechanical.reset();
    return true;
}