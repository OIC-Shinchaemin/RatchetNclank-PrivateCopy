#ifndef MY_REGISTER_GLOBAL_CAMERA_EVENT_H
#define MY_REGISTER_GLOBAL_CAMERA_EVENT_H


#include "Event.h"
#include "My/Core/Observable.h"

#include <memory>

#include "../Camera/AutoCameraController.h"


namespace my {
class RegisterGlobalCameraEvent : public my::Event, public my::Observer<const my::CameraController::CameraInfo&> {
    using super = my::Event;
private:
    //! �ʒm�p
    //my::RegisterGlobalCameraEvent::CameraObservable _camera_subject;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    RegisterGlobalCameraEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~RegisterGlobalCameraEvent();
    /// <summary>
    /// �C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const my::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //my::RegisterGlobalCameraEvent::CameraObservable* GetCameraObservable(void);
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
#endif // !MY_REGISTER_GLOBAL_CAMERA_EVENT_H