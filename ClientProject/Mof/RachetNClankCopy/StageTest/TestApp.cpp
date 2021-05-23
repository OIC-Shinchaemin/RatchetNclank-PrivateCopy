#include "TestApp.h"


MofBool test::CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("Resource");
    bool success = _stage.Load("../Resource/stage/stage.json");
    _stage.Initialize();

    // ƒJƒƒ‰‰Šú‰»
    _camera.SetViewPort();
    _camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
    _camera.LookAt(Mof::CVector3(100.0f, 50.0f, -50.0f), Mof::CVector3(), Mof::CVector3(0.0f, 1.0f, 0.0f));
    _camera.Update();
    ::CGraphicsUtilities::SetCamera(&_camera);


    return TRUE;
}

MofBool test::CGameApp::Input(void) {
    ::g_pInput->RefreshKey();
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        ::PostQuitMessage(0);
        return false;
    } // if

    return TRUE;
}

MofBool test::CGameApp::Update(void) {
    this->Input();

    float delta_time = 1.0f / 60.0f;
    _stage.Update(delta_time);

    return TRUE;
}

MofBool test::CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetRenderTarget(::g_pGraphics->GetRenderTarget(), ::g_pGraphics->GetDepthTarget());
    ::g_pGraphics->SetDepthEnable(true);

    _stage.Render();

    //::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);

    ::g_pGraphics->SetDepthEnable(false);

    ::CGraphicsUtilities::RenderString(10.0f, 30.0f, "FPS = %d", ::CUtilities::GetFPS());
    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool test::CGameApp::Release(void) {
    _stage.Release();
    return TRUE;
}