#include "GameApp.h"

#include "Gamepad.h"
#include "My/Core/Define.h"

#include "Component/Component.h"
#include "Camera/CameraController.h"


void CGameApp::RenderScene(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);
    ::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);


    this->Render3D();

    ::g_pGraphics->SetDepthEnable(false);

    this->Render2D();
}

void CGameApp::Render3D(void) {
    _game_manager->Render();
}

void CGameApp::Render2D(void) {
    //::CGraphicsUtilities::RenderString(10.0f, 10.0f, "fps = %d", ::CUtilities::GetFPS());
    _ui_canvas->Render();
}

MofBool CGameApp::Initialize(void) {
    ::CMofImGui::Setup();
    my::Gamepad::GetInstance().Create();
    ::CUtilities::SetCurrentDirectory("Resource");

    _resource_manager = ut::MakeSharedWithRelease<my::ResourceMgr>();
    _game_manager = ut::MakeSharedWithRelease<my::GameManager>();
    _camera_manager = std::make_shared<my::CameraManager>();
    _ui_canvas = std::make_shared<my::UICanvas>();
    

    my::Component::SetResourceManager(_resource_manager);
    my::Component::SetUICanvas(_ui_canvas);
    my::CameraController::SetCameraManager(_camera_manager);

    _resource_manager->Load("../Resource/resource_path.txt");
    _game_manager->SetResourceManager(_resource_manager);
    _game_manager->SetUICanvas(_ui_canvas);
    _game_manager->Load();
    _game_manager->Initialize();
    return TRUE;
}

MofBool CGameApp::Input(void) {
    ::CMofImGui::Refresh();
    ::g_pInput->RefreshKey();
    ::g_pGamepad->RefreshKey();
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_BACK)) {
        ::PostQuitMessage(0);
        return false;
    } // if

    _game_manager->Input();
    return TRUE;
}

MofBool CGameApp::Update(void) {
    this->Input();
    //float delta = Mof::CUtilities::GetFrameSecond();
    float delta = 0.01667f;
    
    _game_manager->Update(delta);
    _camera_manager->Update();
    _ui_canvas->Update(delta);
    return TRUE;
}

MofBool CGameApp::Render(void) {
    ::CMofImGui::RenderSetup();
    ::g_pGraphics->RenderStart();

    this->RenderScene();

    ::CMofImGui::RenderGui();
    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool CGameApp::Release(void) {
    _ui_canvas.reset();
    _camera_manager.reset();
    _game_manager.reset();
    _resource_manager.reset();

    my::Gamepad::GetInstance().Release();
    ::CMofImGui::Cleanup();
    return TRUE;
}