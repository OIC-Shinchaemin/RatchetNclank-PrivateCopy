#ifndef RATCHET_TITLE_SCENE_H
#define RATCHET_TITLE_SCENE_H


#include "Scene.h"

#include <memory>

#include "Base/Core/ServiceLocator.h"
#include "../GameDefine.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"
#include "../Stage/Stage.h"
#include "../Actor/Character/Player.h"
#include "Base/Core/Observable.h"
#include "../Game/GameManager.h"
#include "../Game/GameSystem/OptionSystem.h"
#include "../UI/TitleInfoMenu.h"


namespace ratchet {
class TitleScene : public ratchet::Scene,
    public base::core::Observer<const ratchet::OptionSystem::Info&> {
    using super = ratchet::Scene;
private:
    //! ステージ
    Stage _stage;
    //! カメラ
    std::shared_ptr<ratchet::Camera> _stage_view_camera;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::CameraController> _camera_controller;
    //! 表示用
    std::shared_ptr<ratchet::Player> _demo_actor;
    //! 通知用
    base::core::Observable<bool> _option_system_subject;
    //! 通知用
    base::core::Observable<bool> _title_menu_subject;
    //! ゲーム
    std::weak_ptr<ratchet::GameManager> _game;
    //! UI地蔵
    ratchet::UICreator<ratchet::TitleInfoMenu> _ui_creator;
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
    TitleScene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TitleScene();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::Actor>& ptr) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const ratchet::OptionSystem::Info& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::GameManager> ptr);
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
    virtual bool Load(std::shared_ptr<ratchet::Scene::Param>  param) override;
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
    virtual bool Release(void);
};
}
#endif // !RATCHET_TITLE_SCENE_H