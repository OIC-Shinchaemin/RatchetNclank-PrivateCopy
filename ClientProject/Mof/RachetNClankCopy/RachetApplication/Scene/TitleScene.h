#ifndef MY_TITLE_SCENE_H
#define MY_TITLE_SCENE_H


#include "Scene.h"

#include <memory>

#include "My/Core/ServiceLocator.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"
#include "../Stage/Stage.h"


namespace my {
class TitleScene : public my::Scene {
    using super = my::Scene;
private:
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! 画面
    std::weak_ptr<Mof::CTexture> _backbround;
    //! ステージ
    Stage _stage;
    //! カメラ
    std::shared_ptr<my::Camera> _stage_view_camera;
    //! カメラコントローラ
    my::ServiceLocator<my::CameraController> _camera_controller;
    //! 水面
    Mof::CTexture _water_surface;
protected:
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
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
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
};
}
#endif // !MY_TITLE_SCENE_H