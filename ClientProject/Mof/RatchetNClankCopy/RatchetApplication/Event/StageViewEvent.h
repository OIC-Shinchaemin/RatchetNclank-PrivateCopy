#ifndef RATCHET_EVENT_STAGE_VIEW_EVENT_H
#define RATCHET_EVENT_STAGE_VIEW_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Camera/Camera.h"
#include "../Camera/AutoCameraController.h"
#include "../Game/GameSystem/HelpDesk.h"
#include "../Scene/GameScene.h"
#include "../Game/GameSystem/Text/TextSystem.h"


namespace ratchet::event {
class StageViewEvent : public ratchet::event::Event {
    using super = ratchet::event::Event;
    using CameraObservable = base::core::Observable<const ratchet::camera::CameraController::CameraInfo&>;
private:
    //! �J����
    std::shared_ptr<ratchet::camera::Camera> _stage_view_camera;
    //! �J�����R���g���[��
    std::shared_ptr<ratchet::camera::AutoCameraController> _stage_view_camera_controller;
    //! �ʒm�p
    ratchet::event::StageViewEvent::CameraObservable _camera_subject;
    //! �J����
    std::weak_ptr<ratchet::game::gamesystem::HelpDesk> _help_desk;
    //! �V�[��
    std::weak_ptr<scene::GameScene> _scene;
    //! �e�L�X�g
    std::weak_ptr<ratchet::game::gamesystem::text::TextSystem> _text_system;
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
    ratchet::event::StageViewEvent::CameraObservable* GetCameraObservable(void);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    void SetHelpDesk(const std::shared_ptr<ratchet::game::gamesystem::HelpDesk>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    void SetGameScene(const std::shared_ptr<ratchet::scene::GameScene>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    void SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem>& ptr);
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
#endif // !RATCHET_EVENT_BRIDGE_EVENT_H