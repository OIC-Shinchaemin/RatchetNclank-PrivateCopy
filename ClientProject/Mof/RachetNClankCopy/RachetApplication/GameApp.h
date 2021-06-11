#pragma once

#include "Mof.h"
#include "ResourceManager.h"
#include "Camera/CameraManager.h"
#include "Light/LightManager.h"
#include "Game/GameManager.h"
#include "Event/EventManager.h"
#include "Base/UI/UICanvas.h"
#include "Scene/SceneManager.h"
#include "GameDefine.h"


class CGameApp : public CSingleGameApplication {
private:
    //! リソース
    std::shared_ptr<rachet::ResourceMgr> _resource_manager;
    //! カメラ
    std::shared_ptr<rachet::CameraManager> _camera_manager;
    //! ライト
    std::shared_ptr<rachet::LightManager> _light_manager;
    //! ゲーム
    std::shared_ptr<rachet::GameManager> _game_manager;
    //! イベント
    std::shared_ptr<rachet::EventManager> _event_manager;
    //! UI
    std::shared_ptr<base::ui::UICanvas> _ui_canvas;
    //! シーン
    std::shared_ptr<rachet::SceneManager> _scene_manager;
public:
    CGameApp() :
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