#ifndef MY_GAME_SCENE_H
#define MY_GAME_SCENE_H


#include "Scene.h"

#include <memory>
#include <vector>

#include "My/Core/ServiceLocator.h"
#include "My/Core/Observer.h"
#include "My/UI/UICanvas.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"
#include "../Camera/AutoCameraController.h"
#include "../Game/GameWorld.h"
#include "../Game/Renderer.h"
#include "../Game/PhysicsWorld.h"
#include "../Stage/Stage.h"
#include "../Game/GameManager.h"
#include "../BridgeEvent.h"
#include "../ShipEvent.h"


namespace my {
class GameScene : public my::Scene {
    using super = my::Scene;
private:
    //! 追加
    std::vector<std::shared_ptr<my::Actor>> _created_actors;
    //! 削除
    std::vector<std::shared_ptr<my::Actor>> _delete_actors;
    //! ゲーム
    my::GameWorld _game_world;
    //! レンダラー
    my::Renderer _renderer;
    //! コリジョン
    my::PhysicsWorld _physic_world;
    //! ステージ
    Stage _stage;
    //! 再初期化
    bool _re_initialize;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! ゲーム
    std::weak_ptr<my::GameManager> _game;
    //! 削除
    //std::vector<std::shared_ptr<my::Actor>> _for_bridge_event_actors;
    std::shared_ptr<my::BridgeEvent>  _bridge_event;
    //! ゲームイベント
    std::shared_ptr<my::ShipEvent>  _ship_event;
    //! ゲームイベント
    //my::Observable<const char*, const std::shared_ptr<my::Actor>& > _bridge_event_subject;
    //! カメラ
    std::shared_ptr<my::Camera> _stage_view_camera;
    //! カメラコントローラ
    my::ServiceLocator<my::CameraController> _stage_view_camera_controller;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// 再初期化
    /// </summary>
    void ReInitialize(void);
protected:
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool SceneUpdate(float delta_time) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool LoadingUpdate(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool LoadingRender(void) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameScene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameScene();
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
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<my::GameManager> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) override;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<my::Scene::Param>  param) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_GAME_SCENE_H