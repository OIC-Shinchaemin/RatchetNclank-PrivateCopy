#pragma once
#include "Character.h"

// à⁄ìÆë¨ìx
#define		CHARACTER_MOVESPEED			(0.015f)
#define		CHARACTER_SLOWMOVESPEEDMAX		(0.03f)
#define		CHARACTER_FASTMOVESPEEDMAX		(0.25f)
// âÒì]ë¨ìx
#define		CHARACTER_ROTATIONSPEED		(0.2f)
//çUåÇâÒêî
#define		CHARACTER_ATTACKCOUNT		(3)
#define		CHARACTER_ATTACKMOVETIME	(0.1f)

#define		GRAVITY					(0.01f)

class Player : public my::Character
{
private:
	enum ActionState
	{
		None,
		Attack1,
		Attack2,
		Attack3,
		JumpStart,
		JumpUp,
		JumpDown,
		JumpEnd,
		Jump2,

	};
	enum MoveState
	{
		Wait,
		MoveSlow,
		MoveFast,
	};
	using super = my::Character;
	CXGamePad				m_GamePad;
	CMeshContainer			m_Mesh;
	CMeshContainer			m_WeaponMesh;
	LPMeshMotionController	m_pMotion;
	CVector2				m_CameraAngle;
	ActionState				m_State;
	MoveState				m_MoveState;
	float					m_StickTilt;
	float					m_MoveAngle;
	float					m_Time;
	bool					m_bJump;
	bool					m_bJump2;
	bool					m_bAttackMove;
	bool					m_bNextAtc;
	CVector3				m_Pos;
	CVector3				m_Move;
	CVector3				m_Angle;
	float					m_Gravity;
	bool					m_bStage;

	virtual bool Input(void);
	void UpdateMove(void);
	void ChangeAnimation(void);
	void CollisionStage(LPMeshContainer pMesh);
public:
	Player();
	~Player();
	bool Load(void);
	virtual bool Initialize(const def::Transform& transform) override;
	virtual bool Update(float delta_time, LPMeshContainer stageMesh);
	virtual bool Render(void) override;
	virtual bool Release(void) override;
};

