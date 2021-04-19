#ifndef MY_CAMERA_COMPONENT_H
#define MY_CAMERA_COMPONENT_H


#include "UpdateComponent.h"

#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


namespace my {
class CameraComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! �Ώ�
    Mof::CVector3 _target;
    //! �J����
    std::shared_ptr<my::Camera> _player_view_camera;
    //! �J�����R���g���[��
    my::CameraController _camera_controller;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void ControllByKeyboard(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void ControllByGamepad(void);
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
};
}
#endif // !MY_CAMERA_COMPONENT_H