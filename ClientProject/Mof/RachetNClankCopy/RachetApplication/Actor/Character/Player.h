#pragma once


#include "Character.h"
#include "My/Core/Observer.h"

#include "../../Camera/Camera.h"
#include "../../Camera/CameraController.h"
#include "../Weapon/Mechanical.h"
#include "../../GameSystem/WeaponSystem.h"


// à⁄ìÆë¨ìx
#define		CHARACTER_MOVESPEED			(0.015f* 60) 
#define		CHARACTER_SLOWMOVESPEEDMAX		(0.03f* 60)
//#define		CHARACTER_FASTMOVESPEEDMAX		(0.25f)
#define		CHARACTER_FASTMOVESPEEDMAX		(0.1f* 60)
// âÒì]ë¨ìx
#define		CHARACTER_ROTATIONSPEED		(0.2f)
//çUåÇâÒêî
#define		CHARACTER_ATTACKCOUNT		(3)
#define		CHARACTER_ATTACKMOVETIME	(0.1f)

#define		GRAVITY					(0.01f)

class Player : public my::Character, public my::Observer<std::shared_ptr<my::Mechanical>> {
public:
    enum class MotionType {
        IdleWait,
        MoveRun,
        CountMax,
    };
private:
    enum ActionState {
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
    enum MoveState {
        Wait,
        MoveSlow,
        MoveFast,
    };
    using super = my::Character;
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
    float					m_Gravity;

    //! ïêäÌ
    std::weak_ptr<my::Mechanical>_current_mechanical;
public:
    Player();
    ~Player();
    virtual void OnNotify(std::shared_ptr<my::Mechanical> change) override;

    virtual bool Initialize(my::Actor::Param* param) override;
    virtual bool Update(float delta_time) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;
};