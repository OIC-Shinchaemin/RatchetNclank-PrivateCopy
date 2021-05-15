#ifndef MY_CAMERA_CONTROLLER_H
#define MY_CAMERA_CONTROLLER_H


#include <memory>

#include "My/Core/Math.h"
#include "Camera.h"
#include "CameraManager.h"


namespace my {
class CameraController {
public:
    struct CameraInfo {
        Mof::CVector3 position;
        Mof::CVector3 target;
    };
protected:
    //! �}�l�[�W��
    static std::weak_ptr<my::CameraManager> _manager;
    //! �J����
    std::shared_ptr<my::Camera>_camera;
    //! �΂˒萔
    const float _spring;
    //! �����萔
    const float _dumping;
    //! �ʒu
    Mof::CVector3 _position;
    //! �Ώ�
    Mof::CVector3 _target;
    // ����
    float _distance;
    //! Z���𒆐S�Ƃ������ʊp��
    math::Radian _azimuth;
    //! XY���ʋ�̕����t��]�p�x�i�p�j��
    math::Radian _altitude;
    //! ���x
    Mof::CVector3 _velocity;
    //! �Ώ�
    Mof::CVector3 _preview_position;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(const std::shared_ptr<my::Camera>& camera);
    /// <summary>
    /// �����W�n�����s���W�n
    /// </summary>
    /// <param name="camera"></param>
    Mof::CVector3 SphericalToCartesian(Mof::CVector3 spherical) const;
    Mof::CVector3 SphericalToCartesian(float x, float y, float z) const;
public:
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    static void SetCameraManager(const std::shared_ptr<my::CameraManager>& ptr);
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~CameraController();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetCamera(const std::shared_ptr<my::Camera>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetCameraPosition(Mof::CVector3 pos);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetCameraTarget(Mof::CVector3 pos);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="value"></param>
    void SetDistance(float value);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="azimuth"></param>
    void SetAzimuth(float degree);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="degree"></param>
    void SetAltitude(float degree);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Camera> GetCamera(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetCameraPosition(void) const;
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
    float GetAzimuth(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetAltitude(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDefaultAzimuth(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDefaultAltitude(void) const;
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
    /// ��]
    /// </summary>
    /// <param name="degree"></param>
    virtual void AddAzimuth(float degree);
    /// <summary>
    /// ��]
    /// </summary>
    /// <param name="degree"></param>
    virtual void AddAltitude(float degree);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasValidCamara(void) const;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool RegisterGlobalCamera(void);
};
}
#endif // !MY_CAMERA_CONTROLLER_H