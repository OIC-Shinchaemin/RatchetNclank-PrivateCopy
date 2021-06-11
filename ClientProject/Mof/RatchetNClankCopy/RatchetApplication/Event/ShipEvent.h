#ifndef RATCHET_SHIP_EVENT_H
#define RATCHET_SHIP_EVENT_H


#include "Event.h"
#include "Base/Core/Observer.h"

#include <memory>

#include "BridgeEvent.h"
#include "../Stage/StageObject.h"
#include "../Camera/PointCameraController.h"


namespace ratchet {
namespace event {
class ShipEvent : public ratchet::event::Event,
    public base::core::Observer<const ratchet::CameraController::CameraInfo&>,
    public base::core::Observer<const char*, const std::shared_ptr<StageObject>&> {
    using super = ratchet::event::Event;
private:
    //! �ʒm�p
    base::core::Observable<const char*, const std::shared_ptr<ratchet::Actor>& > _ship_event_subject;
    //! �J����
    std::shared_ptr<ratchet::Camera> _ship_view_camera;
    //! �J�����R���g���[��
    ratchet::PointCameraController _ship_view_camera_controller;
    //! �ʒu
    Mof::CVector3 _ideal_position;
    //! �J�������
    ratchet::CameraController::CameraInfo _info;
    //! �v���C���[�r���[
    std::weak_ptr<base::core::Observer<const ratchet::CameraController::CameraInfo&>> _camera_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ShipEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ShipEvent();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<StageObject>& ptr) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const ratchet::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const char*, const std::shared_ptr<ratchet::Actor>&>* GetShipEventSubject(void);
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
}
#endif // !RATCHET_SHIP_EVENT_H