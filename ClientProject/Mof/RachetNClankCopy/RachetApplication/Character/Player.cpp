#include "Player.h"

#include "../Gamepad.h"


bool Player::Input(void) {
    super::Input();

    float h = ::g_pGamepad->GetStickHorizontal();
    float v = ::g_pGamepad->GetStickVertical();
    if (MOF_ABS(h) < MOF_ABS(v)) {
        m_StickTilt = MOF_ABS(v) * 0.5f;
    }
    else {
        m_StickTilt = MOF_ABS(h) * 0.5f;
    }
    if (MOF_ABS(h) > 0.4f && MOF_ABS(h) <= 0.7f && MOF_ABS(v) <= 0.7f
        || MOF_ABS(v) > 0.4f && MOF_ABS(h) <= 0.7f && MOF_ABS(v) <= 0.7f) {
        m_MoveState = MoveSlow;
        m_MoveAngle = atan2f(-v, h) + MOF_MATH_HALFPI;
    }
    else if (MOF_ABS(h) > 0.5f || MOF_ABS(v) > 0.5f) {
        m_MoveState = MoveFast;
        m_MoveAngle = atan2f(-v, h) + MOF_MATH_HALFPI;
    }
    else {
        m_MoveState = Wait;
    }

    float rh = ::g_pGamepad->GetRightStickHorizontal();
    float rv = ::g_pGamepad->GetRightStickVertical();
    if (MOF_ABS(rh) > 0.2f) {
        m_CameraAngle.x += rh * 0.024f;
    }
    if (MOF_ABS(rv) > 0.2f) {
        m_CameraAngle.y += rv * 0.01f;
    }
    else {
        if (m_CameraAngle.y > 0.01f) {
            m_CameraAngle.y -= 0.01f;
        }
        else if (m_CameraAngle.y < -0.01f) {
            m_CameraAngle.y += 0.01f;
        }
        else {
            m_CameraAngle.y = 0.0f;
        }
    }

    if (::g_pGamepad->IsKeyPull(XINPUT_A)) {
        m_Time = 0.22f;
    }
    else if (::g_pGamepad->IsKeyPush(XINPUT_A)) {
        if (m_State == JumpUp && !m_bJump2 && m_Time >= 0) {
            m_bJump2 = true;
            m_Time = 10.0f;
        }
        else if (m_State == None) {
            m_bJump = true;
            m_State = JumpStart;
            m_bJump2 = false;
            m_Time = 10.0f;
        }
    }
    else if (::g_pGamepad->IsKeyPush(XINPUT_X)) {
        if (m_State == None) {
            m_State = Attack1;
            m_bAttackMove = false;
        }
        else if (m_State == Attack1 || m_State == Attack2) {
            m_bNextAtc = true;
        }
    }
    return true;
}

bool Player::Update(float delta_time) {
    this->Update(delta_time, NULL);
    return true;
}

void Player::UpdateCamera(void) {
    auto pos = super::GetPosition();
    CVector3 cpos = pos;
    CVector3 tpos = pos;
    CVector3 fvec(0, 0, -1);
    fvec.RotationY(m_CameraAngle.x);
    fvec.RotationX(m_CameraAngle.y);
    cpos.y += 2.0f;
    tpos.y += 1.5f;
    cpos -= fvec * 4.2f;
    tpos += fvec * 0.5f;

    /*
    if (m_State == JumpUp || m_State == JumpDown || m_State == Jump2) {
        cpos.y = m_Camera.GetViewPosition().y;
        tpos.y = m_Camera.GetTargetPosition().y;
    }
    m_Camera.LookAt(cpos, tpos, CVector3(0, 1, 0));
    m_Camera.Update();
    */
}

void Player::UpdateMove(void) {
    auto angle_y = super::GetRotate().y;

    if (m_State == Attack1 && !m_bAttackMove ||
        m_State == Attack2 && !m_bAttackMove ||
        m_State == Attack3 && !m_bAttackMove) {

        CVector3 fvec(0, 0, -1);
        //fvec.RotationY(m_Angle.y);
        fvec.RotationY(angle_y);
        m_Move += fvec * 0.2f;
        m_bAttackMove = true;
    }

    if (m_MoveState == Wait || m_State != None && !m_bJump) {
        float ml = m_Move.Length();
        if (ml > CHARACTER_MOVESPEED) {
            m_Move.Normal(m_Move);
            m_Move *= (ml - CHARACTER_MOVESPEED);
        }
        else {
            m_Move.SetValue(0.0f, 0.0f, 0.0f);
        }
        return;
    }
    //カメラの前方向のベクトル
    //CVector3 cfvec = m_Camera.GetViewFront();
    CVector3 cfvec = _camera_controller->GetViewFront();
    //カメラのY軸の回転角度を求める
    float cy = atan2(cfvec.z, -cfvec.x) + MOF_MATH_HALFPI;
    //移動角度を求める
    float my = m_MoveAngle + cy;
    MOF_NORMALIZE_RADIANANGLE(my);
    //差分角度
    float sa = my - angle_y;
    MOF_ROTDIRECTION_RADIANANGLE(sa);
    //回転
    angle_y += MOF_CLIPING(sa, -CHARACTER_ROTATIONSPEED * m_StickTilt, CHARACTER_ROTATIONSPEED * m_StickTilt);
    MOF_NORMALIZE_RADIANANGLE(angle_y);

    //移動方向のベクトル
    CVector3 fvec(0, 0, -1);
    fvec.RotationY(my);
    m_Move += fvec * CHARACTER_MOVESPEED;
    //移動を最高速度でクリップする
    float ml = m_Move.Length();
    float ms = 0.0f;
    if (m_MoveState == MoveSlow) {
        ms = CHARACTER_SLOWMOVESPEEDMAX;
    }
    else if (m_MoveState == MoveFast) {
        ms = CHARACTER_FASTMOVESPEEDMAX;
    }

    if (ml >= ms) {
        m_Move.Normal(m_Move);
        m_Move *= ms;
    }

    auto rotate = super::GetRotate();
    rotate.y = angle_y;
    super::SetRotate(rotate);
}

void Player::UpdateJump(void) {
    if (JumpStart == m_State && _motion->IsEndMotion()) {
        m_Gravity = 0.2f;
        m_State = JumpUp;
    }
    else if (JumpUp == m_State) {
        if (m_Time < 0) {
            m_Gravity = 0.0f;
            m_State = JumpDown;
        }
        if (m_Gravity < 0) {
            if (m_bJump2) {
                m_State = Jump2;
            }
            else {
                m_State = JumpDown;
            }
        }
    }
    else if (Jump2 == m_State && _motion->IsEndMotion()) {
        m_State = JumpDown;
    }
    else if (JumpDown == m_State && _motion->IsEndMotion()) {
        //m_State = None;
    }
    else if (m_State == JumpEnd) {
        m_State = None;
        m_bJump = false;
    }
}

void Player::UpdateAttack(void) {
    if (m_State != Attack1 && m_State != Attack2 && m_State != Attack3) {
        return;
    }
    if (m_State == Attack1 && _motion->IsEndMotion() && m_bNextAtc) {
        m_State = Attack2;
        m_bNextAtc = false;
        m_bAttackMove = false;
    }
    else if (m_State == Attack2 && _motion->IsEndMotion() && m_bNextAtc) {
        m_State = Attack3;
        m_bNextAtc = false;
        m_bAttackMove = false;
    }
    else if (_motion->IsEndMotion() && !m_bNextAtc) {
        m_State = None;
        m_bAttackMove = false;
    }
}

void Player::ChangeAnimation(void) {
    if (m_State != None) {
        switch (m_State) {
            case Player::None:
                break;
            case Player::Attack1:
                _motion->ChangeMotionByName("atk_attack_01_ft", 1.0f, FALSE, FALSE);
                break;
            case Player::Attack2:
                _motion->ChangeMotionByName("atk_attack_02_ft", 1.0f, FALSE, FALSE);
                break;
            case Player::Attack3:
                _motion->ChangeMotionByName("atk_attack_03_ft", 1.0f, FALSE, FALSE);
                break;
            case Player::JumpStart:
                _motion->ChangeMotionByName("mov_jump_f_set", 1.0f, FALSE, FALSE);
                break;
            case Player::JumpUp:
                _motion->ChangeMotionByName("mov_jump_f_u_lp", 1.0f, FALSE, FALSE);
                break;
            case Player::JumpDown:
                _motion->ChangeMotionByName("mov_jump_f_d_lp", 1.0f, FALSE, FALSE);
                break;
            case Player::JumpEnd:
                _motion->ChangeMotionByName("mov_jump_landing", 1.0f, FALSE, TRUE);
                break;
            case Player::Jump2:
                _motion->ChangeMotionByName("mov_m_step_f", 1.0f, FALSE, FALSE);
                break;
            default:
                break;
        }
    }
    else {
        switch (m_MoveState) {
            case Player::Wait:
                _motion->ChangeMotionByName("bse_wait_lp", 1.0f, TRUE, FALSE);
                break;
            case Player::MoveSlow:
                _motion->ChangeMotionByName("mov_run_lp", 0.5f, TRUE, FALSE);
                break;
            case Player::MoveFast:
                _motion->ChangeMotionByName("mov_run_lp", 1.0f, TRUE, FALSE);
                break;
            default:
                break;
        }
    }
}

Player::Player() :
    m_WeaponMesh(),
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
    //m_Pos(),
    m_Move(),
    //m_Angle(),
    m_Gravity(),
    m_bStage(),
    _player_view_camera(),
    _top_view_camera(),
    _camera_controller(std::make_shared<my::CameraController>()){
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/Chara/Chr_01_ion_mdl_01.mom");
}

Player::~Player() {
}

bool Player::Load(void) {
    /*
    if (!m_Mesh.Load("Character/Chr_01_ion_mdl_01.mom")) {
        return false;
    }
    _motion = m_Mesh.CreateMotionController();
    if (!m_WeaponMesh.Load("Character/Wep_01_ion_mdl_01.mom")) {
        return false;
    }
    */
    return true;
}

bool Player::Initialize(const def::Transform& transform) {
    super::Initialize(transform);
    {
        _top_view_camera = (std::make_shared<my::Camera>());
        _top_view_camera->SetPosition(Mof::CVector3(0.0f, 1.5f, 5.0f));
        _top_view_camera->SetTarget(math::vec3::kUnitY * 2.0f);
        _top_view_camera->Initialize();

        _player_view_camera = (std::make_shared<my::Camera>());
        auto pos = Mof::CVector3(0.0f, 5.0f, 5.0f);
       _player_view_camera->SetPosition(pos);
       _player_view_camera->SetTarget(math::vec3::kZero);
       _player_view_camera->Initialize();
       _camera_controller->SetCamera(_player_view_camera);

        my::CameraLocator::RegisterGlobalCamera(_player_view_camera);
    }


    if (auto mesh = _mesh.lock()) {
        _motion = mesh->CreateMotionController();
        _motion->ChangeMotion(0);
    } // if
    
    if (!m_WeaponMesh.Load("../Resource/mesh/Character/Wep_01_ion_mdl_01.mom")) {
        return false;
    }


    //m_Pos = Vector3(0, 0, 0);
    m_State = None;
    m_MoveState = Wait;
    m_bJump2 = false;
    m_Time = 0.0f;
    /*
    m_Camera.SetViewPort();
    m_Camera.LookAt(CVector3(-2, 2, -2), CVector3(0, 0, 0), CVector3(0.0f, 1.0f, 0.0f));
    m_Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
    UpdateCamera();
    CGraphicsUtilities::SetCamera(&m_Camera);
    */
    return true;
}

bool Player::Update(float delta_time, LPMeshContainer stageMesh) {
    super::Update(delta_time);

    m_Time -= CUtilities::GetFrameSecond();
    //Input();
    UpdateMove();
    //UpdateJump();
    //UpdateAttack();

    auto pos = super::GetPosition();
    pos += m_Move;
    //m_Pos += m_Move;



    /*if (m_State != Jump2)
    {
        m_Gravity -= GRAVITY;
    }*/
    if (pos.y < 0) {
        m_MoveState = Wait;
        pos.y = 0;
    }
    pos.y += m_Gravity;

    super::SetPosition(pos);

    //CollisionStage(stageMesh);

    ChangeAnimation();

//    UpdateCamera();
    float height = 2.0f;
    _camera_controller->SetCameraTarget(Mof::CVector3(pos.x, pos.y + height, pos.z));
    _camera_controller->Update();
    return true;
}

bool Player::Render(void) {
    super::Render();

    //武器を設定するボーンの情報を取得する
    LPBONEMOTIONSTATE pBoneState = _motion->GetBoneState("UPP_weapon");
    if (!pBoneState) {
        return false;
    }
    //武器メッシュを描画する行列をボーン情報から計算する
    CMatrix44 matWeapon = pBoneState->pBone->GetRotationOffsetMatrix() * pBoneState->BoneMatrix;
    //武器メッシュの描画
    m_WeaponMesh.Render(matWeapon);
    return true;
}

bool Player::Release(void) {
    super::Release();
    _player_view_camera.reset();
    _camera_controller.reset();

    MOF_SAFE_DELETE(_motion);

    m_WeaponMesh.Release();
    return true;
}
/*
void Player::CollisionStage(LPMeshContainer pMesh)
{
    //判定初期化
    m_bStage = false;
    //接触情報
    COLLISIONOUTGEOMETRY gout;
    //進行方向へのレイ
    CRay3D mray(m_Pos, m_Move);
    mray.Position.y += 0.5f;
    if (mray.CollisionMesh(pMesh, gout))
    {
        if (gout.d <= m_Move.Length() + 1.0f)
        {
            float nd = CVector3Utilities::Dot(m_Move, gout.Normal);
            nd = MOF_ABS(nd);
            m_Pos += mray.Direction * (gout.d - (1.0f - nd));
            m_Pos += gout.Normal * nd;
            m_bStage = true;
        }
    }
    //下方向へのレイ
    CRay3D dray(m_Pos, CVector3(0, -1, 0));
    dray.Position.y += 2.0f;
    if (dray.CollisionMesh(pMesh, gout))
    {
        if (gout.d <= 2.1f)
        {
            m_Pos.y += 2.1f - gout.d;

            if (m_State == JumpDown && m_Gravity < 0)
            {
                m_State = JumpEnd;
            }

            //通常状態での地面への接触処理
            if (m_Gravity < 0)
            {
                m_Gravity = 0.0f;
            }
        }
    }
}
*/