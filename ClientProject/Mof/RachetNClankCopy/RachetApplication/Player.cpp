#include "Player.h"

bool Player::Input(void)
{
	super::Input();
	float h = m_GamePad.GetStickHorizontal();
	float v = m_GamePad.GetStickVertical();
	if (MOF_ABS(h) < MOF_ABS(v))
	{
		m_StickTilt = MOF_ABS(v) * 0.5f;
	}
	else
	{
		m_StickTilt = MOF_ABS(h) * 0.5f;
	}
	if (MOF_ABS(h) > 0.4f && MOF_ABS(h) <= 0.7f && MOF_ABS(v) <= 0.7f
		|| MOF_ABS(v) > 0.4f && MOF_ABS(h) <= 0.7f && MOF_ABS(v) <= 0.7f)
	{
		m_MoveState = MoveSlow;
		m_MoveAngle = atan2f(-v, h) + MOF_MATH_HALFPI;
	}
	else if (MOF_ABS(h) > 0.5f || MOF_ABS(v) > 0.5f)
	{
		m_MoveState = MoveFast;
		m_MoveAngle = atan2f(-v, h) + MOF_MATH_HALFPI;
	}
	else
	{
		m_MoveState = Wait;
	}

	float rh = m_GamePad.GetRightStickHorizontal();
	float rv = m_GamePad.GetRightStickVertical();
	if (MOF_ABS(rh) > 0.2f)
	{
		m_CameraAngle.x += rh * 0.024f;
	}
	if (MOF_ABS(rv) > 0.2f)
	{
		m_CameraAngle.y += rv * 0.01f;
	}
	else
	{
		if (m_CameraAngle.y > 0.01f)
		{
			m_CameraAngle.y -= 0.01f;
		}
		else if (m_CameraAngle.y < -0.01f)
		{
			m_CameraAngle.y += 0.01f;
		}
		else
		{
			m_CameraAngle.y = 0.0f;
		}
	}

	if (m_GamePad.IsKeyPull(XINPUT_A))
	{
		m_Time = 0.22f;
	}
	else if (m_GamePad.IsKeyPush(XINPUT_A))
	{
		if (m_State == JumpUp && !m_bJump2 && m_Time >= 0)
		{
			m_bJump2 = true;
			m_Time = 10.0f;
		}
		else if (m_State == None)
		{
			m_bJump = true;
			m_State = JumpStart;
			m_bJump2 = false;
			m_Time = 10.0f;
		}
	}
	else if (m_GamePad.IsKeyPush(XINPUT_X))
	{
		if (m_State == None)
		{
			m_State = Attack1;
			m_bAttackMove = false;
		}
		else if (m_State == Attack1 || m_State == Attack2)
		{
			m_bNextAtc = true;
		}
	}
	return true;
}

void Player::UpdateMove(void)
{
	if (m_State == Attack1 && !m_bAttackMove ||
		m_State == Attack2 && !m_bAttackMove ||
		m_State == Attack3 && !m_bAttackMove)
	{
		CVector3 fvec(0, 0, -1);
		fvec.RotationY(m_Angle.y);
		m_Move += fvec * 0.2f;
		m_bAttackMove = true;
	}

	if (m_MoveState == Wait || m_State != None && !m_bJump)
	{
		float ml = m_Move.Length();
		if (ml > CHARACTER_MOVESPEED)
		{
			m_Move.Normal(m_Move);
			m_Move *= (ml - CHARACTER_MOVESPEED);
		}
		else
		{
			m_Move.SetValue(0.0f, 0.0f, 0.0f);
		}
		return;
	}
	//カメラの前方向のベクトル
	CVector3 cfvec /*= m_Camera.GetViewFront()*/;
	//カメラのY軸の回転角度を求める
	float cy = atan2(cfvec.z, -cfvec.x) + MOF_MATH_HALFPI;
	//移動角度を求める
	float my = m_MoveAngle + cy;
	MOF_NORMALIZE_RADIANANGLE(my);
	//差分角度
	float sa = my - m_Angle.y;
	MOF_ROTDIRECTION_RADIANANGLE(sa);
	//回転
	m_Angle.y += MOF_CLIPING(sa, -CHARACTER_ROTATIONSPEED * m_StickTilt, CHARACTER_ROTATIONSPEED * m_StickTilt);
	MOF_NORMALIZE_RADIANANGLE(m_Angle.y);

	//移動方向のベクトル
	CVector3 fvec(0, 0, -1);
	fvec.RotationY(my);
	m_Move += fvec * CHARACTER_MOVESPEED;
	//移動を最高速度でクリップする
	float ml = m_Move.Length();
	float ms = 0.0f;
	if (m_MoveState == MoveSlow)
	{
		ms = CHARACTER_SLOWMOVESPEEDMAX;
	}
	else if (m_MoveState == MoveFast)
	{
		ms = CHARACTER_FASTMOVESPEEDMAX;
	}

	if (ml >= ms)
	{
		m_Move.Normal(m_Move);
		m_Move *= ms;
	}
}

void Player::UpdateJump(void)
{
	if (JumpStart == m_State && m_pMotion->IsEndMotion())
	{
		m_Gravity = 0.2f;
		m_State = JumpUp;
	}
	else if (JumpUp == m_State)
	{
		if (m_Time < 0)
		{
			m_Gravity = 0.0f;
			m_State = JumpDown;
		}
		if (m_Gravity < 0)
		{
			if (m_bJump2)
			{
				m_State = Jump2;
			}
			else
			{
				m_State = JumpDown;
			}
		}
	}
	else if (Jump2 == m_State && m_pMotion->IsEndMotion())
	{
		m_State = JumpDown;
	}
	else if (JumpDown == m_State && m_pMotion->IsEndMotion())
	{
		//m_State = None;
	}
	else if (m_State == JumpEnd)
	{
		m_State = None;
		m_bJump = false;
	}
}

void Player::ChangeAnimation(void)
{
	if (m_State != None)
	{
		switch (m_State)
		{
		case Player::None:
			break;
		case Player::Attack1:
			m_pMotion->ChangeMotionByName("atk_attack_01_ft", 1.0f, FALSE, FALSE);
			break;
		case Player::Attack2:
			m_pMotion->ChangeMotionByName("atk_attack_02_ft", 1.0f, FALSE, FALSE);
			break;
		case Player::Attack3:
			m_pMotion->ChangeMotionByName("atk_attack_03_ft", 1.0f, FALSE, FALSE);
			break;
		case Player::JumpStart:
			m_pMotion->ChangeMotionByName("mov_jump_f_set", 1.0f, FALSE, FALSE);
			break;
		case Player::JumpUp:
			m_pMotion->ChangeMotionByName("mov_jump_f_u_lp", 1.0f, FALSE, FALSE);
			break;
		case Player::JumpDown:
			m_pMotion->ChangeMotionByName("mov_jump_f_d_lp", 1.0f, FALSE, FALSE);
			break;
		case Player::JumpEnd:
			m_pMotion->ChangeMotionByName("mov_jump_landing", 1.0f, FALSE, TRUE);
			break;
		case Player::Jump2:
			m_pMotion->ChangeMotionByName("mov_m_step_f", 1.0f, FALSE, FALSE);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (m_MoveState)
		{
		case Player::Wait:
			m_pMotion->ChangeMotionByName("bse_wait_lp", 1.0f, TRUE, FALSE);
			break;
		case Player::MoveSlow:
			m_pMotion->ChangeMotionByName("mov_run_lp", 0.5f, TRUE, FALSE);
			break;
		case Player::MoveFast:
			m_pMotion->ChangeMotionByName("mov_run_lp", 1.0f, TRUE, FALSE);
			break;
		default:
			break;
		}
	}
}

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Load(void)
{
	if (!m_Mesh.Load("Character/Chr_01_ion_mdl_01.mom"))
	{
		return false;
	}
	m_pMotion = m_Mesh.CreateMotionController();
	if (!m_WeaponMesh.Load("Character/Wep_01_ion_mdl_01.mom"))
	{
		return false;
	}
	return true;
}

bool Player::Initialize(const def::Transform& transform)
{
	super::Initialize(transform);
	XGAMEPADCREATEINFO info;
	info.No = 0;
	m_GamePad.Create(&info);

	m_Pos = Vector3(0, 0, 0);
	m_State = None;
	m_bJump2 = false;
	m_Time = 0.0f;

	return true;
}

bool Player::Update(float delta_time, LPMeshContainer stageMesh)
{
	super::Update(delta_time);

	m_GamePad.RefreshKey();
	m_Time -= CUtilities::GetFrameSecond();
	m_pMotion->AddTimer(CUtilities::GetFrameSecond());
	Input();
	UpdateMove();
	//UpdateJump();
	//UpdateAttack();

	m_Pos += m_Move;
	/*if (m_State != Jump2)
	{
		m_Gravity -= GRAVITY;
	}*/
	if (m_Pos.y < 0)
	{
		m_MoveState = Wait;
		m_Pos.y = 0;
	}
	m_Pos.y += m_Gravity;

	//CollisionStage(stageMesh);

	ChangeAnimation();
	//UpdateCamera();
	return true;
}

bool Player::Render(void)
{
	super::Render();

	CMatrix44 matWorld;
	matWorld.RotationZXY(m_Angle);
	matWorld.SetTranslation(m_Pos);
	m_pMotion->RefreshBoneMatrix(matWorld);
	m_Mesh.Render(m_pMotion);

	//武器を設定するボーンの情報を取得する
	LPBONEMOTIONSTATE pBoneState = m_pMotion->GetBoneState("UPP_weapon");
	if (!pBoneState)
	{
		return false;
	}
	//武器メッシュを描画する行列をボーン情報から計算する
	CMatrix44 matWeapon = pBoneState->pBone->GetRotationOffsetMatrix() * pBoneState->BoneMatrix;
	//武器メッシュの描画
	m_WeaponMesh.Render(matWeapon);
	return true;
}

bool Player::Release(void)
{
	MOF_SAFE_DELETE(m_pMotion);
	m_Mesh.Release();
	m_WeaponMesh.Release();
	super::Release();
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