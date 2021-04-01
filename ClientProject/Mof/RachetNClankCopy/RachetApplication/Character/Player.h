#pragma once


#include "Character.h"
#include "../Camera/CameraLocator.h"

#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


// �ړ����x
#define		CHARACTER_MOVESPEED			(0.015f* 60) 
#define		CHARACTER_SLOWMOVESPEEDMAX		(0.03f* 60)
//#define		CHARACTER_FASTMOVESPEEDMAX		(0.25f)
#define		CHARACTER_FASTMOVESPEEDMAX		(0.1f* 60)
// ��]���x
#define		CHARACTER_ROTATIONSPEED		(0.2f)
//�U����
#define		CHARACTER_ATTACKCOUNT		(3)
#define		CHARACTER_ATTACKMOVETIME	(0.1f)

#define		GRAVITY					(0.01f)

class Player : public my::Character, private my::CameraLocator {
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
    CVector2				_camera_angle;
    ActionState				_state;
    MoveState				_move_state;
    float					_stick_tilt;
    float					_move_angle;
    float					_time;
    bool					_jump;
    bool					_jump2;
    bool					_attack_move;
    bool					_next_atc;
    float					_gravity;
    
    //! �J����
    std::shared_ptr<my::Camera> _player_view_camera;
    //! �J����
    std::shared_ptr<my::Camera> _top_view_camera;
    //! �J�����R���g���[��
    std::shared_ptr<my::CameraController>_camera_controller;

    virtual void InputMoveAngularVelocity(Mof::CVector2 stick, float speed) override;
    void InputCameraForKeyboard(float angular_speed, float speed);
    void InputCameraForGamepad(float angular_speed, float speed);
    void UpdateCamera(void);
    void UpdateMove(void);
    void UpdateJump(void);
    void UpdateAttack(void);
    virtual void UpdateTransform(float delta_time) override;
    void ChangeAnimation(void);
public:
    Player();
    ~Player();

    virtual bool Initialize(const def::Transform& transform) override;
    virtual bool Input(void) override;
    virtual bool Update(float delta_time) override;
    virtual bool Update(float delta_time, LPMeshContainer stage_mesh);
    virtual bool Render(void) override;
    virtual bool Release(void) override;
};