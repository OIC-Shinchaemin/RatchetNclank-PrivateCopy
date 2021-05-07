#ifndef MY_TITLE_SCENE_H
#define MY_TITLE_SCENE_H


#include "Scene.h"

#include <memory>

#include "My/Core/ServiceLocator.h"
#include "../GameDefine.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"
#include "../Stage/Stage.h"


namespace my {
class TitleScene : public my::Scene {
    using super = my::Scene;

    struct cbUVScrollParam {
        Mof::Vector4 value;

        cbUVScrollParam& operator+=(Mof::CVector2 scroll) {
            value.x += scroll.x;
            value.y += scroll.y;
            return *this;
        }
    };
private:
    //! ステージ
    Stage _stage;
    //! カメラ
    std::shared_ptr<my::Camera> _stage_view_camera;
    //! カメラコントローラ
    my::ServiceLocator<my::CameraController> _camera_controller;
    //! テスト
    Mof::CTexture _mock;
    //! 水面
    Mof::LPGeometry _plane;
    //! スクロール
    Mof::CVector2 _scroll;
    cbUVScrollParam _uv_scroll;
    //シェーダー
    Mof::CShader gShader;
    Mof::CShaderBind_3DPrimitiveBase gShaderBind;
    // 光源
    Mof::CDirectionalLight _simple_light;

    Mof::LPMeshMotionController _motion;
protected:
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
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