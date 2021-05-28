#include "GameApp.h"

#include "Gamepad.h"
#include "My/Core/Define.h"

#include "Factory/FactoryManager.h"
#include "Component/Component.h"
#include "Camera/CameraController.h"


MofBool CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("Resource");

    my::Gamepad::GetInstance().Create();
    _resource_manager = ut::MakeSharedWithRelease<my::ResourceMgr>();
    _camera_manager = std::make_shared<my::CameraManager>();
    _light_manager = std::make_shared<my::LightManager>();
    _game_manager = ut::MakeSharedWithRelease<my::GameManager>();
    _event_manager = ut::MakeSharedWithRelease<my::EventManager>();
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

    _scene_manager->SetResourceManager(_resource_manager);
    _scene_manager->SetGameManager(_game_manager);
    _scene_manager->SetEventManager(_event_manager);
    _scene_manager->SetUICanvas(_ui_canvas);
    _scene_manager->Initialize();
    return TRUE;
}

MofBool CGameApp::Input(void) {
    ::g_pInput->RefreshKey();
    ::g_pGamepad->RefreshKey();

#ifdef _DEBUG
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_BACK)) {
        ::PostQuitMessage(0);
        return false;
    } // if
#endif // _DEBUG
    return TRUE;
}

MofBool CGameApp::Update(void) {
    this->Input();

    float delta = 0.01667f;

    _game_manager->Update();
    _scene_manager->Update(delta);
    _camera_manager->Update();
    _ui_canvas->Update(delta);
    return TRUE;
}

MofBool CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();

    _scene_manager->Render();
#ifdef _DEBUG
    auto fps = ::CUtilities::GetFPS();
    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "fps = %d", fps);
#endif // _DEBUG
    
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