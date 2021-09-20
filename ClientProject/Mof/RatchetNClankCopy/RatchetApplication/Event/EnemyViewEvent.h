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
    //! カメラ
    std::shared_ptr<ratchet::camera::Camera> _camera;
    //! カメラコントローラ
    std::shared_ptr<ratchet::camera::AutoCameraController> _camera_controller;
    //! 次のカメラへの通知用
    ratchet::event::EnemyViewEvent::CameraObservable _camera_subject;
    //! 通知用
    ratchet::event::EnemyViewEventMessageSubject _enemy_view_event_message_subject;
    //! スキップフラグ
    //bool _skip_reserve;
    //! タイマー時間
    //float _skip_time_set;
    //! タイマー
    base::core::Timer _skip_reserve_timer;
    //! 位置
    Mof::CVector3 _start_position;
    //! プレイヤーカメラ
    base::core::ServiceLocator<ratchet::camera::CameraController>* _player_camera_controller;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyViewEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EnemyViewEvent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::event::EnemyViewEvent::CameraObservable* GetCameraObservable(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::event::EnemyViewEventMessageSubject* GetEnemyViewEventMessageSubject(void) {
        return &this->_enemy_view_event_message_subject;
    }
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetStartPosition(Mof::CVector3 pos);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCamera(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    //void SetGameScene(const std::shared_ptr<ratchet::scene::Scene>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    //void SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_EVENT_ENEMY_VIEW_EVENT_H