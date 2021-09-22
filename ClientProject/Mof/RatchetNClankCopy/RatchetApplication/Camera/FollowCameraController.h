#ifndef RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet::camera {
class FollowCameraController: public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    //! ���_�ʒu��ۊǂ���
    bool _enable_interpolate_target_position;
    //! ���z�̈ʒu
    Mof::CVector3 _ideal_target_position;
    //! ���z�̈ʒu
    Mof::CVector3 _interpolate_start_position;
    //! ��Ԏ���
    float _time;
    //! ��Ԏ���
    float _time_max;
    //! ���
    float _interpolate_flag;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateTargetPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera, Mof::CVector3 ideal_position);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FollowCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~FollowCameraController();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="flag"></param>
    void SetInterpolateTargetPositionFlag(bool flag);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H