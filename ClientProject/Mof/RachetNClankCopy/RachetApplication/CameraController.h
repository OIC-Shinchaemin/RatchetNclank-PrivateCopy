#ifndef MY_CAMERA_CONTROLLER_H
#define MY_CAMERA_CONTROLLER_H


#include <memory>

#include "Define.h"

#include "My/Core/Observer.h"
#include "My/Core/Utility.h"
#include "My/Core/Math.h"


namespace my {
class CameraController {
private:
    //! �΂˒萔
    const float kSpring; 
    //! �����萔
    const float kDumping; 
    //! �J����
    std::weak_ptr<class Camera>_camera;
    //! �Ώ�
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
    void SetCamera(const std::shared_ptr<class Camera>& ptr);
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
    /// ��]
    /// </summary>
    /// <param name="degree"></param>
    void AddAzimuth(float degree);
    /// <summary>
    /// ��]
    /// </summary>
    /// <param name="degree"></param>
    void AddAltitude(float degree);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasValidCamara(void) const;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !MY_CAMERA_CONTROLLER_H