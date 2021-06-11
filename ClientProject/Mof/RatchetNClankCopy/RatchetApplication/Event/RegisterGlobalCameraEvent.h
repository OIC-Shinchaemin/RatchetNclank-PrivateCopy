#ifndef RATCHET_REGISTER_GLOBAL_CAMERA_EVENT_H
#define RATCHET_REGISTER_GLOBAL_CAMERA_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Camera/AutoCameraController.h"


namespace ratchet {
class RegisterGlobalCameraEvent : public ratchet::Event, public base::core::Observer<const ratchet::CameraController::CameraInfo&> {
    using super = ratchet::Event;
private:
    //! �ʒm�p
    //ratchet::RegisterGlobalCameraEvent::CameraObservable _camera_subject;
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
    virtual void OnNotify(const ratchet::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //ratchet::RegisterGlobalCameraEvent::CameraObservable* GetCameraObservable(void);
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
#endif // !RATCHET_REGISTER_GLOBAL_CAMERA_EVENT_H