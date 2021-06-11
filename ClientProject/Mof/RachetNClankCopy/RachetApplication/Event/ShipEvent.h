#ifndef MY_SHIP_EVENT_H
#define MY_SHIP_EVENT_H


#include "Event.h"
#include "Base/Core/Observer.h"

#include <memory>

#include "BridgeEvent.h"
#include "../Stage/StageObject.h"
#include "../Camera/PointCameraController.h"


namespace my {
class ShipEvent : public my::Event,
    public my::Observer<const my::CameraController::CameraInfo&>,
    public my::Observer<const char*, const std::shared_ptr<StageObject>&> {
    using super = my::Event;
private:
    //! �ʒm�p
    my::Observable<const char*, const std::shared_ptr<my::Actor>& > _ship_event_subject;
    //! �J����
    std::shared_ptr<my::Camera> _ship_view_camera;
    //! �J�����R���g���[��
    my::PointCameraController _ship_view_camera_controller;
    //! �ʒu
    Mof::CVector3 _ideal_position;
    //! �J�������
    my::CameraController::CameraInfo _info;
    //! �v���C���[�r���[
    std::weak_ptr<my::Observer<const my::CameraController::CameraInfo&>> _camera_com;
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
    virtual void OnNotify(const my::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const char*, const std::shared_ptr<my::Actor>&>* GetShipEventSubject(void);
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
#endif // !MY_SHIP_EVENT_H