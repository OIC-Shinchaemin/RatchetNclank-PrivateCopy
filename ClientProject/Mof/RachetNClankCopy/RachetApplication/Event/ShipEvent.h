#ifndef MY_SHIP_EVENT_H
#define MY_SHIP_EVENT_H


#include "My/Core/Observer.h"

#include <memory>

#include "../Actor.h"
#include "BridgeEvent.h"
#include "../Stage/StageObject.h"
#include "../Camera/FirstPersonCameraController.h"


namespace my {
class ShipEvent :
    public std::enable_shared_from_this<my::ShipEvent>,
    public my::Observer<const char*, const std::shared_ptr<my::Actor>&>,
    public my::Observer<const my::CameraController::CameraInfo&>,
    //public my::Observer<const char*, const std::shared_ptr<my::BridgeEvent>&>,
    public my::Observer<const char*, const std::shared_ptr<StageObject>&>
{
private:
    //! �ʒm�p
    my::Observable<const char*, const std::shared_ptr<my::Actor>& > _ship_event_subject;
    //! �J����
    std::shared_ptr<my::Camera> _ship_view_camera;
    //! �J�����R���g���[��
    my::PointCameraController _ship_view_camera_controller;
    //my::FirstPersonCameraController _ship_view_camera_controller;
    //! �ʒu
    Mof::CVector3 _ideal_position;
    //! �J�������
    my::CameraController::CameraInfo _info;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
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
    my::Observable<const char*, const std::shared_ptr<my::Actor>&>& GetShipEventSubject(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
};
}
#endif // !MY_SHIP_EVENT_H