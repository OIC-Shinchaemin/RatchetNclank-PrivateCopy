#ifndef MY_STAGE_VIEW_EVENT_H
#define MY_STAGE_VIEW_EVENT_H


#include "Event.h"
#include "My/Core/Observable.h"

#include <memory>

#include "../Camera/Camera.h"
#include "../Camera/AutoCameraController.h"


namespace my {
class StageViewEvent : public my::Event, public my::Observable<const char*, const std::shared_ptr<my::StageViewEvent>&> {
    using super = my::Event;
    using Observable = my::Observable<const char*, const std::shared_ptr<my::StageViewEvent>&>;
    using CameraObservable = my::Observable<const my::CameraController::CameraInfo&>;
private:
    //! �J����
    std::shared_ptr<my::Camera> _stage_view_camera;
    //! �J�����R���g���[��
    std::shared_ptr<my::AutoCameraController> _stage_view_camera_controller;
    //! �ʒm
    CameraObservable _subject;
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
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddCameraOvserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr);
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
#endif // !MY_BRIDGE_EVENT_H