#include "TestApp.h"


MofBool test::effect::CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("Resource");

    _resource_manager = ut::MakeSharedWithRelease<ratchet::ResourceMgr>();
    _effect_container.SetResourceManager(_resource_manager);
    _resource_manager->Load("../Resource/scene_resource/game_scene.txt");

    // ƒJƒƒ‰‰Šú‰»
    _camera.SetViewPort();
    _camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
    _camera.LookAt(Mof::CVector3(0.0f, 0.0f, 0.0f), Mof::CVector3(5.0f, -5.0f, -5.0f), Mof::CVector3(0.0f, 1.0f, 0.0f));
    _camera.Update();
    ::CGraphicsUtilities::SetCamera(&_camera);
    return TRUE;
}

MofBool test::effect::CGameApp::Input(void) {
    ::g_pInput->RefreshKey();
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        ::PostQuitMessage(0);
        return false;
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        return false;
    } // if
    return TRUE;
}

MofBool test::effect::CGameApp::Update(void) {
    this->Input();

    float delta_time = 1.0f / 60.0f;
    _effect_container.Update(delta_time);

    return TRUE;
}

MofBool test::effect::CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetRenderTarget(::g_pGraphics->GetRenderTarget(), ::g_pGraphics->GetDepthTarget());
    ::g_pGraphics->SetDepthEnable(true);


    ::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);

    _effect_container.Render();

    ::g_pGraphics->SetDepthEnable(false);

    ::CGraphicsUtilities::RenderString(10.0f, 30.0f, "FPS = %d", ::CUtilities::GetFPS());
    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool test::effect::CGameApp::Release(void) {
    _resource_manager.reset();
    return TRUE;
}