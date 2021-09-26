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
    //! ���\�[�X
    std::shared_ptr<ratchet::ResourceMgr> _resource_manager;
    //! �J����
    std::shared_ptr<ratchet::camera::CameraManager> _camera_manager;
    //! ���C�g
    std::shared_ptr<ratchet::light::LightManager> _light_manager;
    //! �Q�[��
    std::shared_ptr<ratchet::game::GameManager> _game_manager;
    //! �C�x���g
    std::shared_ptr<ratchet::event::EventManager> _event_manager;
    //! UI
    std::shared_ptr<base::ui::UICanvas> _ui_canvas;
    //! �V�[��
    std::shared_ptr<ratchet::scene::SceneManager> _scene_manager;
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