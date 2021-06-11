#ifndef RATCHET_CAMERA_COMPONENT_H
#define RATCHET_CAMERA_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/Observable.h"
#include "Base/Core/ServiceLocator.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


namespace ratchet {
class CameraComponent : public ratchet::UpdateComponent, public base::core::Observer<const ratchet::CameraController::CameraInfo&> {
    using super = ratchet::UpdateComponent;
private:
    //! �Ώ�
    Mof::CVector3 _target;
    //! �J����
    std::shared_ptr<ratchet::Camera> _camera;
    //! �J�����R���g���[��
    base::core::ServiceLocator<ratchet::CameraController> _camera_controller;
    //! ���[�h
    ratchet::CameraController::CameraMode _current_mode;
    //! �R���g���[��
    std::unordered_map<ratchet::CameraController::CameraMode, std::shared_ptr<ratchet::CameraController>> _controller_map;
    
    
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
    std::weak_ptr<class PlayerStateComponent> _state_com;
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
    void UpdateFollow(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
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
    virtual void OnNotify(const ratchet::CameraController::CameraInfo& info) override;
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
    Mof::CVector3 GetPreviewPosition(void) const;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
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
#endif // !RATCHET_CAMERA_COMPONENT_H