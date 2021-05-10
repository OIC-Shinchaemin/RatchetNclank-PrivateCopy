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
    //! ���zFPS
    float _ideal_fps;
    //! ���zFPS
    float _ideal_delta_time;
    //! �f�o�b�O
    bool _debug_flag;
    //! �f�o�b�O
    float _debug_fps;
    //! �f�o�b�O
    float _debug_delta_time;
    //! ���\�[�X
    std::shared_ptr<my::ResourceMgr> _resource_manager;
    //! �Q�[��
    std::shared_ptr<my::GameManager> _game_manager;
    //! �J����
    std::shared_ptr<my::CameraManager> _camera_manager;
    //! ���C�g
    std::shared_ptr<my::LightManager> _light_manager;
    //! UI
    std::shared_ptr<my::UICanvas> _ui_canvas;
    //! �V�[��
    std::shared_ptr<my::SceneManager> _scene_manager;
    /// <summary>
    /// �؂�ւ�
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void ChangeDebugMode(void) noexcept;
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