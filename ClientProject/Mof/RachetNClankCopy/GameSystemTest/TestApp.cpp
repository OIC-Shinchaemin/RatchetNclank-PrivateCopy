#include "TestApp.h"

#include "My/Core/Define.h"
#include "Gamepad.h"


MofBool test::CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("TestResource");
    bool loaded = _gizmo.Load("gizmo.mom");

    my::Gamepad::GetInstance().Create();

        // ƒJƒƒ‰‰Šú‰»
    _camera.SetViewPort();
    _camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
    _camera.LookAt(Mof::CVector3(30.0f, 20.0f, -30.0f), Mof::CVector3(), Mof::CVector3(0.0f, 1.0f, 0.0f));
    _camera.Update();
    ::CGraphicsUtilities::SetCamera(&_camera);
    return TRUE;
}

MofBool test::CGameApp::Input(void) {
    ::g_pInput->RefreshKey();
    ::g_pGamepad->RefreshKey();

    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_BACK)) {
        ::PostQuitMessage(0);
        return false;
    } // if
    return TRUE;
}

MofBool test::CGameApp::Update(void) {
    this->Input();
    return TRUE;
}

MofBool test::CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetRenderTarget(::g_pGraphics->GetRenderTarget(), ::g_pGraphics->GetDepthTarget());
    ::g_pGraphics->SetDepthEnable(true);
    _gizmo.Render(_transform.Matrix());
    _gizmo.Render(Mof::CMatrix44());


    ::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);

    ::g_pGraphics->SetDepthEnable(false);

    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "Game System Test Application ");
    ::CGraphicsUtilities::RenderString(10.0f, 30.0f, "FPS = %d", ::CUtilities::GetFPS());


    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool test::CGameApp::Release(void) {
    my::Gamepad::GetInstance().Release();
    return TRUE;
}