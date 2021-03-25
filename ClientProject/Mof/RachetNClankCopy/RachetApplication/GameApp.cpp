#include "GameApp.h"

#include "My/Core/Define.h"

#include "My/UI/UICanvas.h"
#include "CameraLocator.h"
#include "Character.h"

std::shared_ptr<my::Character> g_pCharacter;


void CGameApp::InitializeGame(void) {
}

void CGameApp::UpdateGame(float delta) {
}

void CGameApp::UpdateUI(float delta) {
}


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
}

void CGameApp::Render2D(void) {
    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "test");
}

MofBool CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("Resource");

    _camera_manager = std::make_shared<my::CameraManager>();
    my::CameraLocator::SetService(_camera_manager);

    g_pCharacter = std::make_shared<my::Character>();
    g_pCharacter->Initialize();
    return TRUE;
}
MofBool CGameApp::Input(void) {
    ::g_pInput->RefreshKey();
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        ::PostQuitMessage(0);
        return false;
    } // if
    return TRUE;
}
MofBool CGameApp::Update(void) {
    this->Input();

    float delta = def::kDeltaTime;

    this->UpdateGame(delta);
    this->UpdateUI(delta);
    _camera_manager->Update();
    return TRUE;
}

MofBool CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();

    this->RenderScene();

    ::g_pGraphics->RenderEnd();
    return TRUE;
}
MofBool CGameApp::Release(void) {
    g_pCharacter->Release();
    return TRUE;
}