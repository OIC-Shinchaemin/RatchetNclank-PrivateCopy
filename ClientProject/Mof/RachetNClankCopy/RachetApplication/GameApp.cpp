#include "GameApp.h"

#include "Gamepad.h"
#include "My/Core/Define.h"
#include "My/UI/CanvasLocator.h"
#include "Camera/CameraLocator.h"
#include "ResourceLocator.h"


void CGameApp::RenderScene(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);
    ::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);


    this->Render3D();

    ::g_pGraphics->SetDepthEnable(false);

    this->Render2D();
}

void CGameApp::Render3D(void) {
    auto render_plane = [](Mof::CVector3 pos, Mof::CVector4 color) {
        Mof::CMatrix44 scale, rotate, translate;
        auto plane = Mof::CMatrix44();
        scale.Scaling(10.0f, 10.0f, 10.0f, scale);
        rotate.RotationY(MOF_ToRadian(0.0f), rotate);
        translate.Translation(pos, translate);
        plane = scale * rotate * translate;
        ::CGraphicsUtilities::RenderPlane(plane, color);
    };
    render_plane(Mof::CVector3(0.0f, 0.0f, -10.0f), def::color_rgba::kRed);
    render_plane(Mof::CVector3(10.0f, 0.0f, 0.0f), def::color_rgba::kGreen);
    render_plane(Mof::CVector3(0.0f, 0.0f, 10.0f), def::color_rgba::kBlue);
    render_plane(Mof::CVector3(-10.0f, 0.0f, 0.0f), def::color_rgba::kYellow);


    Mof::CMatrix44 scale, rotate, translate;
    auto plane = Mof::CMatrix44();
    scale.Scaling(10.0f, 10.0f, 10.0f, scale);
    rotate.RotationY(MOF_ToRadian(0.0f), rotate);
    translate.Translation(0.0f, 0.0f, 0.0f, translate);
    plane = scale * rotate * translate;
    ::CGraphicsUtilities::RenderPlane(plane);

    _game_manager->Render();
}

void CGameApp::Render2D(void) {
    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "test");
    _ui_canvas->Render();
}

MofBool CGameApp::Initialize(void) {
    my::Gamepad::GetInstance().Create();
    ::CUtilities::SetCurrentDirectory("Resource");

    _resource_manager = ut::MakeSharedWithRelease<my::ResourceMgr>();
    _game_manager = ut::MakeSharedWithRelease<my::GameManager>();
    _camera_manager = std::make_shared<my::CameraManager>();
    _ui_canvas = std::make_shared<my::UICanvas>();
    
    my::ResourceLocator::SetService(_resource_manager);
    my::CameraLocator::SetService(_camera_manager);
    my::CanvasLocator::SetService(_ui_canvas);

    _resource_manager->Load("../Resource/resource_path.txt");
    _game_manager->Initialize();
    return TRUE;
}

MofBool CGameApp::Input(void) {
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
    float delta = def::kDeltaTime;

    _game_manager->Update(delta);
    _camera_manager->Update();
    _ui_canvas->Update(delta);
    return TRUE;
}

MofBool CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();

    this->RenderScene();

    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool CGameApp::Release(void) {
    _ui_canvas.reset();
    _camera_manager.reset();
    _game_manager.reset();
    _resource_manager.reset();

    my::Gamepad::GetInstance().Release();
    return TRUE;
}