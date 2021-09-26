#ifndef RATCHET_EVENT_ENEMY_VIEW_EVENT_H
#define RATCHET_EVENT_ENEMY_VIEW_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>


#include "Base/Core/ServiceLocator.h"
#include "../Camera/Camera.h"
#include "../Camera/AutoCameraController.h"
#include "../Scene/Scene.h"
#include "../Scene/GameScene.h"
#include "../Game/GameSystem/Text/TextSystem.h"


namespace ratchet::event {
struct EnemyViewEventEndMessage {
    bool end;
};
using EnemyViewEventEndMessageSubject = base::core::Observable<const EnemyViewEventEndMessage&>;
using EnemyViewEventEndMessageListener = base::core::Observer<const  EnemyViewEventEndMessage&>;
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
    ratchet::event::EnemyViewEventEndMessageSubject _enemy_view_event_message_subject;
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
    //! �ʒm�p
    ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
    //! �e�L�X�g
    std::weak_ptr<ratchet::game::gamesystem::text::TextSystem> _text_system;
    //! ������
    std::weak_ptr<ratchet::scene::GameScene> _game_scene;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void GenerateQueen(void);
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
    /// �Z�b�^�[
    /// </summary>
    void SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem> ptr) {
        this->_text_system = ptr;
    }
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    void SetGameScene(const std::shared_ptr<ratchet::scene::GameScene> ptr) {
        this->_game_scene = ptr;
    }
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
    auto GetTextSystemMessageSubject(void) {
        return  &this->_text_system_message_subject;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::event::EnemyViewEventEndMessageSubject* GetEnemyViewEventMessageSubject(void) {
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