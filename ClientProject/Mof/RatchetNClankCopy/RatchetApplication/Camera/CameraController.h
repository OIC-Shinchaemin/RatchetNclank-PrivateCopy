#ifndef RATCHET_CAMERA_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_CAMERA_CONTROLLER_H


#include <memory>

#include "Base/Core/Math.h"
#include "Camera.h"
#include "CameraManager.h"


namespace ratchet::camera {
class CameraController {
public:
    enum class CameraMode {
        Follow,
        FirstPerson,
        ThirdPerson,
    };
    struct Param {
        //! ���ʊp��
        math::Radian azimuth;
        //! �����t��]�p�x�i�p�j��
        math::Radian altitude;
        // ����
        float distance;
        //! �΂˒萔
        float spring;
        //! �����萔
        float dumping;
        //! ���x
        Mof::CVector3 velocity;
    };
    struct CameraInfo {
        Mof::CVector3 target_position;
        Mof::CVector3 start_position;
        Mof::CVector3 ideal_position;
        Mof::CVector3 camera_front;

        CameraInfo() :
            target_position(),
            start_position(),
            ideal_position(),
            camera_front() {
        }
    };
protected:
    //! �}�l�[�W��
    static std::weak_ptr<ratchet::camera::CameraManager> _manager;
    //! �J����
    std::shared_ptr<ratchet::camera::Camera>_camera;
    //! �ʒu
    Mof::CVector3 _position;
    //! �Ώ�
    Mof::CVector3 _target;
    //! �ʒu
    Mof::CVector3 _preview_position;
    //! �p�����[�^
    ratchet::camera::CameraController::Param _param;
    //! �΂ˎg�p
    bool _use_spring;
public:
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    static void SetCameraManager(const std::shared_ptr<ratchet::camera::CameraManager>& ptr);
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~CameraController();
    /// <summary>
    /// �J�������L����
    /// </summary>
    /// <param name=""></param>
    operator bool(void) const;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetCamera(const std::shared_ptr<ratchet::camera::Camera>& ptr);
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="value"></param>
    void SetSpring(float value);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="value"></param>
    void SetDumping(float value);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="flag"></param>
    void SetUseSpring(bool flag);
    /// <summary>
    /// �Z�b�g
    /// </summary>
    /// <param name="info"></param>
    virtual void SetInfo(const ratchet::camera::CameraController::CameraInfo& info);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::camera::Camera> GetCamera(void) const;
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
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info);
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
#endif // !RATCHET_CAMERA_CAMERA_CONTROLLER_H