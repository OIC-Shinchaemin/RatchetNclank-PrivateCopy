#ifndef RATCHET_EVENT_ENEMY_VIEW_EVENT_H
#define RATCHET_EVENT_ENEMY_VIEW_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>


#include "Base/Core/ServiceLocator.h"
#include "../Camera/Camera.h"
#include "../Camera/AutoCameraController.h"
#include "../Scene/Scene.h"
#include "../Game/GameSystem/Text/TextSystem.h"


namespace ratchet::event {
struct EnemyViewEventMessage {
    bool end;
};
using EnemyViewEventMessageSubject = base::core::Observable<const EnemyViewEventMessage&>;
using EnemyViewEventMessageListener = base::core::Observer<const EnemyViewEventMessage&>;
class EnemyViewEvent : public ratchet::event::Event {
    using super = ratchet::event::Event;
    using CameraObservable = base::core::Observable<const ratchet::camera::CameraController::CameraInfo&>;
private:
    //! �J����
    std::shared_ptr<ratchet::camera::Camera> _camera;
    //! �J�����R���g���[��
    std::shared_ptr<ratchet::camera::AutoCameraController> _camera_controller;
    //! ���̃J�����ւ̒ʒm�p
    ratchet::event::EnemyViewEvent::CameraObservable _camera_subject;
    //! �ʒm�p
    ratchet::event::EnemyViewEventMessageSubject _enemy_view_event_message_subject;
    //! �X�L�b�v�t���O
    //bool _skip_reserve;
    //! �^�C�}�[����
    //float _skip_time_set;
    //! �^�C�}�[
    base::core::Timer _skip_reserve_timer;
    //! �ʒu
    Mof::CVector3 _start_position;
    //! �v���C���[�J����
    base::core::ServiceLocator<ratchet::camera::CameraController>* _player_camera_controller;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyViewEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EnemyViewEvent();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::event::EnemyViewEvent::CameraObservable* GetCameraObservable(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::event::EnemyViewEventMessageSubject* GetEnemyViewEventMessageSubject(void) {
        return &this->_enemy_view_event_message_subject;
    }
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetStartPosition(Mof::CVector3 pos);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCamera(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    //void SetGameScene(const std::shared_ptr<ratchet::scene::Scene>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    //void SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem>& ptr);
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
#endif // !RATCHET_EVENT_ENEMY_VIEW_EVENT_H