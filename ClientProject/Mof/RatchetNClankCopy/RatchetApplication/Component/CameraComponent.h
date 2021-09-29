#ifndef RATCHET_COMPONENT_CAMERA_COMPONENT_H
#define RATCHET_COMPONENT_CAMERA_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/Observable.h"
#include "Base/Core/ServiceLocator.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


namespace ratchet::component::player { class PlayerStateComponent; }
namespace ratchet::component::player { class PlayerComponent; }
namespace ratchet::component {
class CameraComponent : public ratchet::component::UpdateComponent,
    public base::core::Observer<const ratchet::camera::CameraController::CameraInfo&> {
    using super = ratchet::component::UpdateComponent;
private:
    //! �Ώ�
    Mof::CVector3 _target;
    //! �J����
    std::shared_ptr<ratchet::camera::Camera> _camera;
    //! �J�����R���g���[��
    base::core::ServiceLocator<ratchet::camera::CameraController> _camera_controller;
    //! ���[�h
    ratchet::camera::CameraController::CameraMode _current_mode;
    //! �R���g���[��
    std::unordered_map<ratchet::camera::CameraController::CameraMode, std::shared_ptr<ratchet::camera::CameraController>> _controller_map;
    //! FPS�J��������
    float _ideal_fps_camera_angle;
    //! ����
    float _default_distance;
    //! �Ώ�
    Mof::CVector3 _preview_position;
    //! x���ʊpy�p
    Mof::CVector2 _preview_angle;
    //! �Փ˒�
    bool _collisioned_stage;
    //! ���
    std::weak_ptr<ratchet::component::player::PlayerComponent> _player_com;
    //! ���
    std::weak_ptr<ratchet::component::player::PlayerStateComponent> _state_com;
    //! ���b�V��
    std::weak_ptr<class AnimationMeshComponent> _mesh_com;
    //! �Ǐ]�J�������������O�̈ʒu�ōX�V��������
    bool _follow_camera_prev_position_update;
public:
    //! �Ώ�
    base::accessor::Setter<decltype(_preview_position)> preview_position = _preview_position;
    /// <summary>
    /// �L�[�����������̃J��������
    /// </summary>
    /// <param name=""></param>
    void OnPush(void);
    /// <summary>
    /// �L�[�������Ă��鎞�̃J��������
    /// </summary>
    /// <param name=""></param>
    void OnHold(void);
    /// <summary>
    /// �L�[�𗣂������̃J��������
    /// </summary>
    /// <param name=""></param>
    void OnPull(void);
    /// <summary>
    /// �p�x�ݒ�
    /// </summary>
    /// <param name=""></param>
    void TurnLeft(void);
    /// <summary>
    /// �p�x�ݒ�
    /// </summary>
    /// <param name=""></param>
    void TurnRight(void);
    /// <summary>
    /// �p�x�ݒ�
    /// </summary>
    /// <param name=""></param>
    void LookUp(void);
    /// <summary>
    /// �p�x�ݒ�
    /// </summary>
    /// <param name=""></param>
    void LookDown(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateFPSMode(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void ControlByKeyboardFollow(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void ControlByKeyboardFirstPerson(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void ControlByKeyboard(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void ControlByGamepad(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateFollow(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateThirdPerson(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    CameraComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    CameraComponent(const CameraComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CameraComponent();
    /// <summary>
    /// �C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::camera::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="flag"></param>
    void SetFollowCameraPrevPositionUpdateFlag(bool flag);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetCameraController(void) {
        return &this->_camera_controller;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetViewFront(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPosition(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetVelocity(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPreviousPosition(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name=""></param>
    void CollisionStage(void);
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !RATCHET_COMPONENT_CAMERA_COMPONENT_H