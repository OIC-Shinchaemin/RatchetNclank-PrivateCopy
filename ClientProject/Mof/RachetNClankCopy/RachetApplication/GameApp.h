#pragma once

#include "Mof.h"
#include "ResourceManager.h"
#include "Game/GameManager.h"
#include "Camera/CameraManager.h"
#include "Light/LightManager.h"
#include "My/UI/UICanvas.h"
#include "Scene/SceneManager.h"
#include "GameDefine.h"


class CGameApp : public CSingleGameApplication {
private:
    //! 理想FPS
    float _ideal_fps;
    //! 理想FPS
    float _ideal_delta_time;
    //! デバッグ
    bool _debug_flag;
    //! デバッグ
    float _debug_fps;
    //! デバッグ
    float _debug_delta_time;
    //! リソース
    std::shared_ptr<my::ResourceMgr> _resource_manager;
    //! カメラ
    std::shared_ptr<my::CameraManager> _camera_manager;
    //! ライト
    std::shared_ptr<my::LightManager> _light_manager;
    //! ゲーム
    std::shared_ptr<my::GameManager> _game_manager;
    //! UI
    std::shared_ptr<my::UICanvas> _ui_canvas;
    //! シーン
    std::shared_ptr<my::SceneManager> _scene_manager;
    /// <summary>
    /// 切り替え
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void ChangeDebugMode(void) noexcept;
public:
    CGameApp() :
        _ideal_fps(60.0f),
        _ideal_delta_time(1.0f / _ideal_fps),
        _debug_flag(false),
        _debug_fps(_ideal_fps),
        _debug_delta_time(_ideal_delta_time),
        _resource_manager(),
        _camera_manager(),
        _light_manager(),
        _game_manager(),
        _ui_canvas(),
        _scene_manager() {
    }
    virtual ~CGameApp() { Release(); }
    virtual MofBool Initialize(void);
    virtual MofBool Input(void);
    virtual MofBool Update(void);
    virtual MofBool Render(void);
    virtual MofBool Release(void);
};