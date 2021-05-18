#include "GameApp.h"

#include "Gamepad.h"
#include "My/Core/Define.h"

#include "Factory/FactoryManager.h"
#include "Component/Component.h"
#include "Camera/CameraController.h"

#include <filesystem>


void CGameApp::ChangeDebugMode(void) noexcept {
    _debug_flag = !_debug_flag;
}

MofBool CGameApp::Initialize(void) {
    my::Gamepad::GetInstance().Create();

    std::cout << std::filesystem::current_path() ;
    ::CUtilities::SetCurrentDirectory("Resource");
    std::cout << std::filesystem::current_path() ;


    _resource_manager = ut::MakeSharedWithRelease<my::ResourceMgr>();
    _camera_manager = std::make_shared<my::CameraManager>();
    _light_manager = std::make_shared<my::LightManager>();
    _game_manager = ut::MakeSharedWithRelease<my::GameManager>();
    _ui_canvas = std::make_shared<my::UICanvas>();
    _scene_manager = ut::MakeSharedWithRelease<my::SceneManager>();

    my::FactoryManager::Singleton().SetResourceManager(_resource_manager);
    my::Component::SetResourceManager(_resource_manager);
    my::Component::SetUICanvas(_ui_canvas);
    my::CameraController::SetCameraManager(_camera_manager);

    _light_manager->Initialize();

    _game_manager->SetResourceManager(_resource_manager);
    _game_manager->SetUICanvas(_ui_canvas);
    _game_manager->Initialize();

    _scene_manager->SetGameManager(_game_manager);
    _scene_manager->SetResourceManager(_resource_manager);
    _scene_manager->SetUICanvas(_ui_canvas);
    _scene_manager->Initialize();
    return TRUE;
}

MofBool CGameApp::Input(void) {
    ::g_pInput->RefreshKey();
    ::g_pGamepad->RefreshKey();
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_BACK)) {
        ::PostQuitMessage(0);
        return false;
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        this->ChangeDebugMode();
    } // if

    if (_debug_flag) {
        if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
            _debug_fps += _ideal_delta_time;
        } // if
        else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
            _debug_fps -= _ideal_delta_time;
        } // else if
        _debug_delta_time = 1.0f / _debug_fps;
    } // if
    return TRUE;
}

MofBool CGameApp::Update(void) {
    this->Input();

    float delta = 0.01667f;
    if (_debug_flag) {
        delta = _debug_delta_time;
    } // if

    _game_manager->Update();
    _scene_manager->Update(delta);
    _camera_manager->Update();
    _ui_canvas->Update(delta);
    return TRUE;
}

MofBool CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();

    _scene_manager->Render();
    if (_debug_flag) {
        auto fps = ::CUtilities::GetFPS();
        ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "fps = %d", fps);
        ::CGraphicsUtilities::RenderString(10.0f, 60.0f, "debug fps = %f", _debug_fps);
    } // if

    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool CGameApp::Release(void) {
    _ui_canvas.reset();
    _camera_manager.reset();
    _light_manager.reset();
    _game_manager.reset();
    _resource_manager.reset();
    _scene_manager.reset();

    my::Gamepad::GetInstance().Release();
    return TRUE;
}