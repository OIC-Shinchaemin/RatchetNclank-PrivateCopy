#ifndef MY_PLAYER_H
#define MY_PLAYER_H



#include "Character.h"
#include "My/Core/Observer.h"

#include "../Weapon/Mechanical.h"
#include "My/Core/ServiceLocator.h"
#include "../../Camera/Camera.h"
#include "../../Camera/CameraController.h"




namespace my {
	class Player : public my::Character, public my::Observer<std::shared_ptr<my::Mechanical>> {
		using super = my::Character;
	public:
		enum class MotionType {
			IdleWait,
			MoveRun,
			DamageDown,
			CountMax,
		};
	private:

		enum class PlayerState {
			Wait,
			Attack1,
			Attack2,
			Attack3,
			MoveSlow,
			MoveFast,
			JumpStart,
			JumpUp,
			JumpDown,
			JumpEnd,
			DoubleJump,
		};
		//! ����
		std::weak_ptr<my::Mechanical>_current_mechanical;

		//! ���b�V��
		std::weak_ptr<Mof::CMeshContainer> _mesh;
		Mof::LPMeshMotionController	_motion;
		//! �J����
		std::shared_ptr<my::Camera> _player_view_camera;
		//! �J�����R���g���[��
		my::ServiceLocator<my::CameraController> _camera_controller;

		float _character_slow_move_speed_max = 0.03f;
		float _character_move_speed = 0.015f;
		float _character_fast_move_speed_max = 0.25f;
		float _character_rotation_speed = 0.2f;
		float _gravity_increment = 0.1f;
		float _jump_power = 0.13f;
		float _move_angle;
		PlayerState _player_state;
		CVector3 _move;
		float _gravity;
		float _time;
		bool _jump;
		bool _double_jump;
		bool _attack_move;
		bool _Next_attack;

		void UpdateInput(void);
		void UpdateMove(void);
		void UpdateWait(void);
		void UpdateJump(void);
		void UpdateAttack(void);
		void JumpStart(void);
		void ChangeAnimation(void);
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Player();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Player();
		/// <summary>
		/// �ʒm
		/// </summary>
		/// <param name="change"></param>
		virtual void OnNotify(std::shared_ptr<my::Mechanical> change) override;
		bool Generate(const std::shared_ptr<Mof::CMeshContainer>& mesh);
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool Initialize(my::Actor::Param* param) override;
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="delta_time"></param>
		/// <returns></returns>
		virtual bool Update(float delta_time) override;
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Render(void) override;
		/// <summary>
		/// ���
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Release(void) override;
	};
}
#endif // !MY_PLAYER_H