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
    //! 通知アクター
    std::vector<std::shared_ptr<ratchet::Actor>> _for_bridge_event_actors;
    //! ステージ
    Stage* _stage;
    //! カメラ
    std::shared_ptr<ratchet::Camera> _bridge_view_camera;
    //! カメラコントローラ
    ratchet::FirstPersonCameraController _bridge_view_camera_controller;
    //! 位置
    Mof::CVector3 _ideal_position;
    //! 通知用
    base::core::Observable<const ratchet::CameraController::CameraInfo&> _camera_subject;
    //! 通知用
    base::core::Observable<const ratchet::GameQuest&> _quest_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BridgeEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BridgeEvent();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::Actor>& ptr) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetStage(Stage* ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::CameraController::CameraInfo&>* GetCameraSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool EventActorsEmpty(void) const;
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
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddTriggerActor(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    void AllDelete(void);
};
}
}
#endif // !RATCHET_BRIDGE_EVENT_H