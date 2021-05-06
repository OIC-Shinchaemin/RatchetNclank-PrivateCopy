#pragma once

#include "Mof.h"
#include "ResourceManager.h"
#include "Game/GameManager.h"
#include "Camera/CameraManager.h"
#include "My/UI/UICanvas.h"
#include "Scene/SceneManager.h"
#include "GameDefine.h"


class CGameApp : public CSingleGameApplication {
private:
    //! ���\�[�X
    std::shared_ptr<my::ResourceMgr> _resource_manager;
    //! �Q�[��
    std::shared_ptr<my::GameManager> _game_manager;
    //! �J����
    std::shared_ptr<my::CameraManager> _camera_manager;
    //! �J����
    std::shared_ptr<my::UICanvas> _ui_canvas;
    //! �V�[��
    std::shared_ptr<my::SceneManager> _scene_manager;
public:
    CGameApp() {
    }
    virtual ~CGameApp() { Release(); }
    virtual MofBool Initialize(void);
    virtual MofBool Input(void);
    virtual MofBool Update(void);
    virtual MofBool Render(void);
    virtual MofBool Release(void);
};
