#include "Player.h"

#include "../../Gamepad.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/Player/PlayerComponent.h"


void my::Player::UpdateInput(void)
{
    bool key_input = false; bool left = false; bool right = false;
    if (::g_pInput->IsKeyHold(MOFKEY_A)) {
        key_input = true;
        left = true;
        _move_angle = 270.0f;
    } 
    else if (::g_pInput->IsKeyHold(MOFKEY_D)) {
        key_input = true;
        right = true;
        _move_angle = 90.0f;
    } 
    if (::g_pInput->IsKeyHold(MOFKEY_W)) {
        key_input = true;
        _move_angle = 0.0f;
        if (right) {
            _move_angle += 45.0f;
        } 
        else if (left) {
            _move_angle -= 45.0f;
        } 
    } 
    else if (::g_pInput->IsKeyHold(MOFKEY_S)) {
        key_input = true;
        _move_angle = 180.0f;
        if (right) {
           _move_angle -= 45.0f;
        } 
        else if (left) {
            _move_angle += 45.0f;
        } 
    } 
    if (key_input)
    {
        _move_angle   = math::ToRadian(_move_angle) ;
        _player_state = PlayerState::MoveFast;
    }

    if (g_pInput->IsKeyPull(MOFKEY_SPACE))
    {
        key_input = true;
        _time = 0.22f;
    }
    else if (g_pInput->IsKeyPush(MOFKEY_SPACE))
    {
        key_input = true;
        if (_player_state == PlayerState::JumpUp && !_double_jump && _time >= 0)
        {
            _double_jump = true;
            _time = 10.0f;
        }
        else //if (m_State == None)
        {
            this->JumpStart();
        }
    }
    else if (g_pInput->IsKeyPush(MOFKEY_V))
    {
        key_input = true;
        if (_player_state == PlayerState::Wait)
        {
            _player_state = PlayerState::Attack1;
            _attack_move = false;
        }
        else if (_player_state == PlayerState::Attack1 || _player_state == PlayerState::Attack2)
        {
            _Next_attack = true;
        }
    }


    if (key_input)
    {
        return;
    }
    float h = g_pGamepad->GetStickHorizontal();
    float v = g_pGamepad->GetStickVertical();
    if (MOF_ABS(h) > 0.4f && MOF_ABS(h) <= 0.7f && MOF_ABS(v) <= 0.7f
        || MOF_ABS(v) > 0.4f && MOF_ABS(h) <= 0.7f && MOF_ABS(v) <= 0.7f)
    {
        _player_state = PlayerState::MoveSlow;
        _move_angle = atan2f(-v, h) + MOF_MATH_HALFPI;
    }
    else if (MOF_ABS(h) > 0.5f || MOF_ABS(v) > 0.5f)
    {
        _player_state = PlayerState::MoveFast;
        _move_angle = atan2f(-v, h) + MOF_MATH_HALFPI;
    }
    else
    {
        _player_state = PlayerState::Wait;
    }

    if (g_pGamepad->IsKeyPull(XINPUT_A))
    {
        _time = 0.22f;
    }
    else if (g_pGamepad->IsKeyPush(XINPUT_A))
    {
        if (_player_state == PlayerState::JumpUp && !_double_jump && _time >= 0)
        {
            _double_jump = true;
            _time = 10.0f;
        }
        else //if (m_State == None)
        {
            this->JumpStart();
        }
    }
    else if (g_pGamepad->IsKeyPush(XINPUT_X))
    {
        if (_player_state == PlayerState::Wait)
        {
            _player_state = PlayerState::Attack1;
            _attack_move = false;
        }
        else if (_player_state == PlayerState::Attack1 || _player_state == PlayerState::Attack2)
        {
            _Next_attack = true;
        }
    }
}

void my::Player::UpdateMove(void)
{
    

    CVector3 cfvec = _camera_controller.GetService()->GetViewFront();
    float cy = atan2(cfvec.z, -cfvec.x) + MOF_MATH_HALFPI;
    float my = _move_angle + cy;
    MOF_NORMALIZE_RADIANANGLE(my);
    float sa = my - GetRotate().y;
    MOF_ROTDIRECTION_RADIANANGLE(sa);
    CVector3 angle = GetRotate();
    angle.y += MOF_CLIPING(sa, -_character_rotation_speed, _character_rotation_speed);
    SetRotate(angle);
    MOF_NORMALIZE_RADIANANGLE(angle.y);

    CVector3 fvec(0, 0, -1);
    fvec.RotationY(my);
    _move += fvec * _character_move_speed;
    float ml = _move.Length();
    float ms = 0.0f;
    if (_player_state == PlayerState::MoveSlow)
    {
        ms = _character_slow_move_speed_max;
    }
    else if (_player_state == PlayerState::MoveFast)
    {
        ms = _character_fast_move_speed_max;
    }

    if (ml >= ms)
    {
        _move.Normal(_move);
        _move *= ms;
    }
}

void my::Player::UpdateWait(void)
{
    float ml = _move.Length();
    if (ml > _character_move_speed)
    {
        _move.Normal(_move);
        _move *= (ml - _character_move_speed);
    }
    else
    {
        _move.SetValue(0.0f, 0.0f, 0.0f);
    }
}

void my::Player::UpdateJump(void)
{
    if (_player_state == PlayerState::JumpStart && _motion->IsEndMotion())
    {
        _gravity = 0.2f;
        _player_state = PlayerState::JumpUp;
    }
    else if (_player_state == PlayerState::JumpUp)
    {
        if (_time < 0)
        {
            _gravity = 0.0f;
            _player_state = PlayerState::JumpDown;
        }
        if (_gravity < 0)
        {
            if (_double_jump)
            {
                _player_state = PlayerState::DoubleJump;
            }
            else
            {
                _player_state = PlayerState::JumpDown;
            }
        }
    }
    else if (_player_state == PlayerState::DoubleJump && _motion->IsEndMotion())
    {
        _player_state = PlayerState::JumpDown;
    }
    else if (PlayerState::JumpDown == _player_state && _motion->IsEndMotion())
    {
        //m_State = None;
    }
    else if (_player_state == PlayerState::JumpEnd)
    {
        _player_state = PlayerState::Wait;
        _jump = false;
    }
}

void my::Player::JumpStart(void)
{
    _jump = true;
    _player_state = PlayerState::JumpStart;
    _double_jump = false;
    _time = 10.0f;
    _move.y = _jump_power;
}

void my::Player::ChangeAnimation(void)
{
    switch (_player_state)
    {
    case PlayerState::Attack1:
        _motion->ChangeMotionByName("atk_attack_01_ft", 1.0f, FALSE, FALSE);
        break;
    case PlayerState::Attack2:
        _motion->ChangeMotionByName("atk_attack_02_ft", 1.0f, FALSE, FALSE);
        break;
    case PlayerState::Attack3:
        _motion->ChangeMotionByName("atk_attack_03_ft", 1.0f, FALSE, FALSE);
        break;
    case PlayerState::Wait:
        _motion->ChangeMotionByName("bse_wait_lp", 1.0f, TRUE, FALSE);
        break;
    case PlayerState::MoveSlow:
        _motion->ChangeMotionByName("mov_run_lp", 0.5f, TRUE, FALSE);
        break;
    case PlayerState::MoveFast:
        _motion->ChangeMotionByName("mov_run_lp", 1.0f, TRUE, FALSE);
        break;
    case PlayerState::JumpStart:
       _motion->ChangeMotionByName("mov_jump_f_set", 1.0f, FALSE, FALSE);
        break;
    case PlayerState::JumpUp:
        _motion->ChangeMotionByName("mov_jump_f_u_lp", 1.0f, FALSE, FALSE);
        break;
    case PlayerState::JumpDown:
        _motion->ChangeMotionByName("mov_jump_f_d_lp", 1.0f, FALSE, FALSE);
        break;
    case PlayerState::JumpEnd:
        _motion->ChangeMotionByName("mov_jump_landing", 1.0f, FALSE, TRUE);
        break;
    case PlayerState::DoubleJump:
        _motion->ChangeMotionByName("mov_m_step_f", 1.0f, FALSE, FALSE);
        break;
    default:
        break;
    }
}

my::Player::Player() :
    _current_mechanical(),
    _mesh(),
    _motion(),
    _player_view_camera(),
    _camera_controller(),
    _move_angle(0.0f),
    _player_state(),
    _move(),
    _gravity(0.0f),
    _time(0.0f),
    _jump(false),
    _double_jump(false),
    _attack_move(false),
    _Next_attack(false)
{
    super::SetTag("Player");
}

my::Player::~Player() {
}

void my::Player::OnNotify(std::shared_ptr<my::Mechanical> change) {
    _current_mechanical = change;
}

bool my::Player::Generate(const std::shared_ptr<Mof::CMeshContainer>& mesh)
{
    _mesh = mesh;
    if (auto m = _mesh.lock())
    {
        _motion = m->CreateMotionController();
    }
    return false;
}

bool my::Player::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    _player_view_camera = (std::make_shared<my::Camera>());
    auto pos = Mof::CVector3(0.0f, 5.0f, 5.0f);
    _player_view_camera->SetPosition(pos);
    _player_view_camera->SetTarget(math::vec3::kZero);
    _player_view_camera->Initialize();
    _camera_controller.SetService(std::make_shared<my::CameraController>());
    _camera_controller.GetService()->SetCamera(_player_view_camera);
    _camera_controller.GetService()->RegisterGlobalCamera();
    return true;
}

bool my::Player::Update(float delta_time) {
   // super::Updqate(delta_time);
    _time -= CUtilities::GetFrameSecond();
    _motion->AddTimer(CUtilities::GetFrameSecond());

    UpdateInput();
    if (_player_state == PlayerState::MoveFast || _player_state == PlayerState::MoveSlow)
    {
        UpdateMove();
    }
    else if (_player_state == PlayerState::Wait)
    {
        UpdateWait();
    }
    //UpdateMove();
    UpdateJump();

    CVector3 pos = GetPosition();
    pos += _move;
    if (_player_state != PlayerState::DoubleJump)
    {
        //_gravity -= gravity;
    }
    _gravity = _gravity_increment;
    pos.y -= _gravity;
    SetPosition(pos);

    ChangeAnimation();
    if (auto weapon = _current_mechanical.lock()) {
        if (weapon->IsAction() && weapon->CanFire()) {
            auto pos = super::GetPosition();
            auto height = super::GetComponent<my::PlayerComponent>()->GetHeight();
            pos.y += height;
            if (auto target = super::GetComponent<my::PlayerComponent>()->GetTarget().lock()) {
                auto target_pos = target->GetPosition();
                target_pos.y += height;
                weapon->SetLockOnPosition(target_pos);
            } // if
            weapon->Fire(def::Transform(pos, super::GetRotate()));
        } // if
    } // if

    // update child
    if (auto weapon = _current_mechanical.lock()) {
        weapon->Update(delta_time);
    } // if

    float height = 1.0f;
    pos.y += height;
    _camera_controller.GetService()->SetCameraTarget(pos);
    _camera_controller.GetService()->Update();
    return true;
}

bool my::Player::Render(void) {
    //super::Render();
    if (auto r = _mesh.lock()) {
        Mof::CMatrix44 scale, rotate, translate;
        scale.Scaling(super::GetScale(), scale);
        rotate.RotationZXY(super::GetRotate());
        translate.Translation(super::GetPosition(), translate);
        auto world = scale * rotate * translate;

        if (_motion) {
            _motion->RefreshBoneMatrix(world);
            r->Render(_motion);
        } // if
    } // if

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
    MOF_SAFE_DELETE(_motion);
    return true;
}