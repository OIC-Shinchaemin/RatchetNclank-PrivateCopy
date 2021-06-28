#ifndef RATCHET_SCENE_TITLE_SCENE_H
#define RATCHET_SCENE_TITLE_SCENE_H


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
#include "../UI/UICreator.h"


namespace ratchet {
namespace scene {
class TitleLogo {
private:
    //! テクスチャ
    std::weak_ptr<Mof::CTexture> _texture;
    //! 表示
    bool _show;
    //! 表示
    base::core::Timer _show_timer;
public:
    TitleLogo() :
        _texture(),
        _show(false),
        _show_timer() {
        _show_timer.Initialize(3.0f, false);
    }
    ~TitleLogo() {
        _show = false;
    }

    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
        this->_texture = ptr;
    }
    bool Update(float delta_time) {
        if (_show_timer.Tick(delta_time)) {
            _show = true;
        } // if
        return true;
    }
    bool Render(void) {
        if (!_show) {
            return false;
        } // if
        if (auto tex = _texture.lock()) {
            tex->Render(200.0f, 100.0f);
        } // if
        return true;
    }
};


class TitleScene : public ratchet::scene::Scene,
    public base::core::Observer<const ratchet::game::gamesystem::OptionSystem::Info&> {
    using super = ratchet::scene::Scene;
private:
    //! ステージ
    Stage _stage;
    //! カメラ
    std::shared_ptr<ratchet::camera::Camera> _stage_view_camera;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::camera::CameraController> _camera_controller;
    //! 表示用
    std::shared_ptr<ratchet::actor::character::Player> _demo_actor;
    //! 通知用
    base::core::Observable<bool> _option_system_subject;
    //! 通知用
    base::core::Observable<bool> _title_menu_subject;
    //! ゲーム
    std::weak_ptr<ratchet::game::GameManager> _game;
    //! UI地蔵
    ratchet::ui::UICreator<ratchet::ui::TitleInfoMenu> _ui_creator;
    //! タイトル
    TitleLogo _logo;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const ratchet::game::gamesystem::OptionSystem::Info& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr);
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
    virtual bool Load(std::shared_ptr<super::Param>  param) override;
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
}
#endif // !RATCHET_SCENE_TITLE_SCENE_H