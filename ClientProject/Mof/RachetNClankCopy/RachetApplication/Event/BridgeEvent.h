#ifndef MY_BRIDGE_EVENT_H
#define MY_BRIDGE_EVENT_H


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


namespace my {
class BridgeEvent : public my::Event, public my::Observer<const char*, const std::shared_ptr<my::Actor>&> {
    using super = my::Event;
private:
    //! 通知アクター
    std::vector<std::shared_ptr<my::Actor>> _for_bridge_event_actors;
    //! ステージ
    Stage* _stage;
    //! カメラ
    std::shared_ptr<my::Camera> _bridge_view_camera;
    //! カメラコントローラ
    my::FirstPersonCameraController _bridge_view_camera_controller;
    //! 位置
    Mof::CVector3 _ideal_position;
    //! 通知用
    my::Observable<const my::CameraController::CameraInfo&> _camera_subject;
    //! 通知用
    my::Observable<const my::GameQuest&> _quest_subject;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
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
    my::Observable<const my::CameraController::CameraInfo&>* GetCameraSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const my::GameQuest&>* GetQuestSubject(void);
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
    void AddTriggerActor(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    void AllDelete(void);
};
}
#endif // !MY_BRIDGE_EVENT_H