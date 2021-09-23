#ifndef RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet::camera {
class FollowCameraController: public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    //! 視点位置を保管する
    bool _enable_interpolate_target_position;
    //! 理想の位置
    Mof::CVector3 _ideal_target_position;
    //! 理想の位置
    Mof::CVector3 _interpolate_start_position;
    //! 補間時間
    float _time;
    //! 補間時間
    float _time_max;
    //! 補間
    float _interpolate_flag;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateTargetPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera, Mof::CVector3 ideal_position);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FollowCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~FollowCameraController();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="flag"></param>
    void SetInterpolateTargetPositionFlag(bool flag);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H