#ifndef RATCHET_BRIDGE_EVENT_H
#define RATCHET_BRIDGE_EVENT_H


#include "Event.h"
#include "Base/Core/Observer.h"
#include "Base/Core/Observable.h"

#include <memory>
#include <vector>

#include "../Actor.h"
#include "../Stage/Stage.h"
#include "../Camera/Camera.h"
#include "../Camera/FirstPersonCameraController.h"
#include "../Game/GameSystem/GameQuest.h"


namespace ratchet {
namespace event {
class BridgeEvent : public ratchet::event::Event, public base::core::Observer<const char*, const std::shared_ptr<ratchet::Actor>&> {
    using super = ratchet::event::Event;
private:
    //! �ʒm�A�N�^�[
    std::vector<std::shared_ptr<ratchet::Actor>> _for_bridge_event_actors;
    //! �X�e�[�W
    Stage* _stage;
    //! �J����
    std::shared_ptr<ratchet::Camera> _bridge_view_camera;
    //! �J�����R���g���[��
    ratchet::FirstPersonCameraController _bridge_view_camera_controller;
    //! �ʒu
    Mof::CVector3 _ideal_position;
    //! �ʒm�p
    base::core::Observable<const ratchet::CameraController::CameraInfo&> _camera_subject;
    //! �ʒm�p
    base::core::Observable<const ratchet::GameQuest&> _quest_subject;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BridgeEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BridgeEvent();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::Actor>& ptr) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetStage(Stage* ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::CameraController::CameraInfo&>* GetCameraSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool EventActorsEmpty(void) const;
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
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddTriggerActor(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name=""></param>
    void AllDelete(void);
};
}
}
#endif // !RATCHET_BRIDGE_EVENT_H