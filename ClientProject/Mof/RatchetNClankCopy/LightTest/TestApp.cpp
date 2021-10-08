#include "TestApp.h"


//カメラ
CCamera						gCamera;
//メッシュ
LPGeometry					pGeometry;

MofBool test::light::CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("Resource");
    
    gCamera.SetViewPort();
    gCamera.LookAt(Vector3(-2.0f * 10, 2.0f * 10, -2.0f * 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
    gCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
    gCamera.Update();
    CGraphicsUtilities::SetCamera(&gCamera);
    //メッシュの読み込み
    pGeometry = CGraphicsUtilities::CreatePlaneGeometry(1000, 1000, 1, 1, TRUE, Vector3(0, 0, 0));

    _light_manager = std::make_shared<ratchet::light::LightManager>();
    _light_manager->Initialize();
    auto create_info = ratchet::light::LightPillarCreateInfo();
    create_info.position = Mof::CVector3();
    _light_manager->CreateLightPillar(create_info);
    return TRUE;
}

MofBool test::light::CGameApp::Input(void) {
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

MofBool test::light::CGameApp::Update(void) {
    this->Input();

    float delta_time = 1.0f / 60.0f;
    return TRUE;
}

MofBool test::light::CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetRenderTarget(::g_pGraphics->GetRenderTarget(), ::g_pGraphics->GetDepthTarget());
    ::g_pGraphics->SetDepthEnable(true);


    ::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);
    _light_manager->Render();


    ::g_pGraphics->SetDepthEnable(false);

    ::CGraphicsUtilities::RenderString(10.0f, 30.0f, "FPS = %d", ::CUtilities::GetFPS());
    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool test::light::CGameApp::Release(void) {
    _light_manager->Release();
    _light_manager.reset();
    delete pGeometry;
    pGeometry = nullptr;
    return TRUE;
}