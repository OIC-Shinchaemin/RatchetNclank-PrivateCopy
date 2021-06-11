#ifndef RACHET_STAGE_VIEW_EVENT_H
#define RACHET_STAGE_VIEW_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Camera/Camera.h"
#include "../Camera/AutoCameraController.h"


namespace rachet {
class StageViewEvent : public rachet::Event {
    using super = rachet::Event;
    using CameraObservable = base::core::Observable<const rachet::CameraController::CameraInfo&>;
private:
    //! �J����
    std::shared_ptr<rachet::Camera> _stage_view_camera;
    //! �J�����R���g���[��
    std::shared_ptr<rachet::AutoCameraController> _stage_view_camera_controller;
    //! �ʒm�p
    rachet::StageViewEvent::CameraObservable _camera_subject;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    StageViewEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~StageViewEvent();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    rachet::StageViewEvent::CameraObservable* GetCameraObservable(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !RACHET_BRIDGE_EVENT_H