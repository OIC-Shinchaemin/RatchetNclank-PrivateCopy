#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"


//void Player::UpdateCamera(void) {
//    auto pos = super::GetPosition();
//    CVector3 cpos = pos;
//    CVector3 tpos = pos;
//    CVector3 fvec(0, 0, -1);
//    fvec.RotationY(m_CameraAngle.x);
//    fvec.RotationX(m_CameraAngle.y);
//    cpos.y += 2.0f;
//    tpos.y += 1.5f;
//    cpos -= fvec * 4.2f;
//    tpos += fvec * 0.5f;
//}
//
//void Player::UpdateMove(void) {
//
//    if (m_State == Attack1 && !m_bAttackMove ||
//        m_State == Attack2 && !m_bAttackMove ||
//        m_State == Attack3 && !m_bAttackMove) {
//
//        CVector3 fvec(0, 0, -1);
//        fvec.RotationY(angle_y);
//        //m_Move += fvec * 0.2f;
//        super::_velocity.AddVelocityForce(fvec * 0.2f);
//        m_bAttackMove = true;
//    }
//
//    if (m_MoveState == Wait || m_State != None && !m_bJump) {
//        auto move = super::_velocity.GetVelocity();
//        float ml = move.Length();
//        if (ml > CHARACTER_MOVESPEED) {
//            move.Normal(move);
//            move *= (ml - CHARACTER_MOVESPEED);
//            super::_velocity.SetVelocity(move);
//        }
//        else {
//            move.SetValue(0.0f, 0.0f, 0.0f);
//            super::_velocity.SetVelocity(move);
//        }
//        return;
//    }
//    //カメラの前方向のベクトル
//    CVector3 cfvec = _camera_controller.GetViewFront();
//    //カメラのY軸の回転角度を求める
//    float cy = atan2(cfvec.z, -cfvec.x) + MOF_MATH_HALFPI;
//    //移動角度を求める
//    float my = m_MoveAngle + cy;
//    MOF_NORMALIZE_RADIANANGLE(my);
//    //差分角度
//    float sa = my - angle_y;
//    MOF_ROTDIRECTION_RADIANANGLE(sa);
//    //回転
//    angle_y += MOF_CLIPING(sa, -CHARACTER_ROTATIONSPEED * m_StickTilt, CHARACTER_ROTATIONSPEED * m_StickTilt);
//    MOF_NORMALIZE_RADIANANGLE(angle_y);
//
//    //移動方向のベクトル
//    CVector3 fvec(0, 0, -1);
//    fvec.RotationY(my);
//    //m_Move += fvec * CHARACTER_MOVESPEED;
//    super::_velocity.AddVelocityForce(fvec * CHARACTER_MOVESPEED);
//
//    //移動を最高速度でクリップする
//    auto move = super::_velocity.GetVelocity();
//    float ml = move.Length();
//    float ms = 0.0f;
//    if (m_MoveState == MoveSlow) {
//        ms = CHARACTER_SLOWMOVESPEEDMAX;
//    }
//    else if (m_MoveState == MoveFast) {
//        ms = CHARACTER_FASTMOVESPEEDMAX;
//    }
//
//    if (ml >= ms) {
//        move.Normal(move);
//        move *= ms;
//        super::_velocity.SetVelocity(move);
//    }
//
//    auto rotate = super::GetRotate();
//    rotate.y = angle_y;
//    super::SetRotate(rotate);
//}
//
//void Player::UpdateJump(void) {
//    if (JumpStart == m_State && _motion->IsEndMotion()) {
//        m_Gravity = 0.2f;
//        m_State = JumpUp;
//    }
//    else if (JumpUp == m_State) {
//        if (m_Time < 0) {
//            m_Gravity = 0.0f;
//            m_State = JumpDown;
//        }
//        if (m_Gravity < 0) {
//            if (m_bJump2) {
//                m_State = Jump2;
//            }
//            else {
//                m_State = JumpDown;
//            }
//        }
//    }
//    else if (Jump2 == m_State && _motion->IsEndMotion()) {
//        m_State = JumpDown;
//    }
//    else if (JumpDown == m_State && _motion->IsEndMotion()) {
//        //m_State = None;
//    }
//    else if (m_State == JumpEnd) {
//        m_State = None;
//        m_bJump = false;
//    }
//}
//
//void Player::UpdateAttack(void) {
//    if (m_State != Attack1 && m_State != Attack2 && m_State != Attack3) {
//        return;
//    }
//    if (m_State == Attack1 && _motion->IsEndMotion() && m_bNextAtc) {
//        m_State = Attack2;
//        m_bNextAtc = false;
//        m_bAttackMove = false;
//    }
//    else if (m_State == Attack2 && _motion->IsEndMotion() && m_bNextAtc) {
//        m_State = Attack3;
//        m_bNextAtc = false;
//        m_bAttackMove = false;
//    }
//    else if (_motion->IsEndMotion() && !m_bNextAtc) {
//        m_State = None;
//        m_bAttackMove = false;
//    }
//}
//
//void Player::UpdateTransform(float delta_time) {
//    auto owner = this;
//    // rotate
//    auto rotate = this->UpdateRotate(delta_time, owner->GetRotate(), _velocity.GetAngularVelocity());
//    owner->SetRotate(rotate);
//    // position
//    auto pos = this->UpdatePosition(delta_time, owner->GetPosition(), _velocity.GetVelocity());
//    if (pos.y < 0.0f) {
//        pos.y = 0.0f;
//    } // if
//    owner->SetPosition(pos);
//}
//
//void Player::ChangeAnimation(void) {
//    if (m_State != None) {
//        switch (m_State) {
//            case Player::None:
//                break;
//            case Player::Attack1:
//                _motion->ChangeMotionByName("atk_attack_01_ft", 1.0f, FALSE, FALSE);
//                break;
//            case Player::Attack2:
//                _motion->ChangeMotionByName("atk_attack_02_ft", 1.0f, FALSE, FALSE);
//                break;
//            case Player::Attack3:
//                _motion->ChangeMotionByName("atk_attack_03_ft", 1.0f, FALSE, FALSE);
//                break;
//            case Player::JumpStart:
//                _motion->ChangeMotionByName("mov_jump_f_set", 1.0f, FALSE, FALSE);
//                break;
//            case Player::JumpUp:
//                _motion->ChangeMotionByName("mov_jump_f_u_lp", 1.0f, FALSE, FALSE);
//                break;
//            case Player::JumpDown:
//                _motion->ChangeMotionByName("mov_jump_f_d_lp", 1.0f, FALSE, FALSE);
//                break;
//            case Player::JumpEnd:
//                _motion->ChangeMotionByName("mov_jump_landing", 1.0f, FALSE, TRUE);
//                break;
//            case Player::Jump2:
//                _motion->ChangeMotionByName("mov_m_step_f", 1.0f, FALSE, FALSE);
//                break;
//            default:
//                break;
//        }
//    }
//    else {
//        switch (m_MoveState) {
//            case Player::Wait:
//                _motion->ChangeMotionByName("bse_wait_lp", 1.0f, TRUE, FALSE);
//                break;
//            case Player::MoveSlow:
//                _motion->ChangeMotionByName("mov_run_lp", 0.5f, TRUE, FALSE);
//                break;
//            case Player::MoveFast:
//                _motion->ChangeMotionByName("mov_run_lp", 1.0f, TRUE, FALSE);
//                break;
//            default:
//                break;
//        }
//    }
//}

Player::Player() :
    m_CameraAngle(),
    m_State(),
    m_MoveState(),
    m_StickTilt(),
    m_MoveAngle(),
    m_Time(),
    m_bJump(),
    m_bJump2(),
    m_bAttackMove(),
    m_bNextAtc(),
    m_Gravity(),
    _current_mechanical() {
    super::SetTag("Player");
}

Player::~Player() {
}

void Player::OnNotify(std::shared_ptr<my::Mechanical> change) {
    _current_mechanical = change;
}

bool Player::Initialize(my::Actor::Param* param) {
    super::Initialize(param);

    m_State = None;
    m_MoveState = Wait;
    m_bJump2 = false;
    m_Time = 0.0f;
    return true;
}

bool Player::Update(float delta_time) {
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
/*
bool Player::Update(float delta_time, LPMeshContainer stageMesh) {
    super::Update(delta_time);

    m_Time -= CUtilities::GetFrameSecond();
    UpdateMove();
    UpdateJump();
    UpdateAttack();


    this->UpdateTransform(delta_time);
    ChangeAnimation();

    UpdateCamera();
    return true;
}
*/

bool Player::Render(void) {
    super::Render();

    // 武器を設定するボーンの情報を取得する
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

bool Player::Release(void) {
    super::Release();
    _current_mechanical.reset();
    return true;
}