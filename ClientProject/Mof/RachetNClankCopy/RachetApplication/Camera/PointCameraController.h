#ifndef MY_POINT_CAMERA_CONTROLLER_H
#define MY_POINT_CAMERA_CONTROLLER_H


#include "CameraController.h"
#include "My/Core/Observable.h"


namespace my {
class PointCameraController : public my::CameraController,
    public my::Observable<const my::CameraController::CameraInfo&> {
    using super = my::CameraController;
    using Observable = my::Observable<const my::CameraController::CameraInfo&>;
private:
    //! �ʒu
    Mof::CVector3 _ideal_position;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PointCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~PointCameraController();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="info"></param>
    virtual void SetInfo(const my::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddObserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const my::CameraController::CameraInfo& info) override;
};
}
#endif // !MY_POINT_CAMERA_CONTROLLER_H