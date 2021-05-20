#ifndef MY_CAMERA_COMPONENT_H
#define MY_CAMERA_COMPONENT_H


#include "UpdateComponent.h"

#include "My/Core/Observable.h"
#include "My/Core/ServiceLocator.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


namespace my {
class CameraComponent : public my::UpdateComponent, public my::Observer<const my::CameraController::CameraInfo&> {
    using super = my::UpdateComponent;
    enum class CameraMode {
        Follow,
        FirstPerson,
    };
private:
    //! �Ώ�
    Mof::CVector3 _target;
    //! �J����
    std::shared_ptr<my::Camera> _camera;
    //! �J�����R���g���[��
    my::ServiceLocator<my::CameraController> _camera_controller;
    //! ���[�h
    my::CameraComponent::CameraMode _current_mode;
    //! �R���g���[��
    std::unordered_map<my::CameraComponent::CameraMode, std::shared_ptr<my::CameraController>> _controller_map;
    
    
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
    /// �ݒ�
    /// </summary>
    /// <param name=""></param>
    void IdealAngle(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateFPSMode(void);
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    void ExitFPSMode(void);
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
    void UpdateFollow(float delta_time, std::shared_ptr<my::CameraController> controller);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateFirstPerson(float delta_time, std::shared_ptr<my::CameraController> controller);
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
    virtual void OnNotify(const my::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector3 pos);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetTarget(Mof::CVector3 pos);
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
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
#endif // !MY_CAMERA_COMPONENT_H