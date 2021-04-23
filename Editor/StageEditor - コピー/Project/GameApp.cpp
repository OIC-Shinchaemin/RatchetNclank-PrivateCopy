/*************************************************************************//*!

                    @file    GameApp.cpp
                    @brief    基本ゲームアプリ。

                                                            @author    濱田　享
                                                            @date    2014.05.14
*//**************************************************************************/

#include    <imgui/MofImGui.h>

//INCLUDE
#include    "GameApp.h"
#include    "utilities/EditorUtilities.h"
#include    "EditorParameter.h"
#include    "stage/Stage.h"

CXGamePad   gamepad;

CCamera     main_camera;

std::string resource_dir = "";

Stage       stage;

/*************************************************************************//*!
        @brief            アプリケーションの初期化
        @param            None

        @return            TRUE        成功<br>
                        それ以外    失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

    CUtilities::SetCurrentDirectory("Resource");
    editor::EditorUtilities::LoadWindowParam();

    CMofImGui::Setup(false, false);

    resource_dir = std::filesystem::current_path().string();
    theParam.Add(ParamKey::ResourcePath, &resource_dir);

    float scene_w = g_pGraphics->GetTargetWidth();
    float scene_h = g_pGraphics->GetTargetHeight();

    main_camera.PerspectiveFov(MOF_ToRadian(60), scene_w / scene_h, 0.1f, 500.0f);
    main_camera.LookAt(Vector3(0.0f, 2.0f, -6.0f), Vector3(0, 0.5f, 0), Vector3(0, 1, 0));
    main_camera.SetViewPort();
    main_camera.Update();

    CGraphicsUtilities::SetCamera(&main_camera);

    XGAMEPADCREATEINFO pad_info;
    pad_info.No = 0;
    gamepad.Create(&pad_info);

    stage.Load("stage/test.json");
    stage.Initialize();

    return TRUE;
}
/*************************************************************************//*!
        @brief            アプリケーションの更新
        @param            None

        @return            TRUE        成功<br>
                        それ以外    失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
    CMofImGui::Refresh();
    //キーの更新
    g_pInput->RefreshKey();
    gamepad.RefreshKey();
    editor::EditorUtilities::ObserveWindowStyle();

    if (std::optional<RECT> rect = editor::EditorUtilities::ChangeWindowSize()) {
        float w = rect.value().right;
        float h = rect.value().bottom;
        main_camera.PerspectiveFov(MOF_ToRadian(60), w / h, 0.1f, 500.0f);
        main_camera.SetViewPort();
        main_camera.Update();
    }

    stage.Update(0.01667f);


    if (g_pInput->IsKeyPush(MOFKEY_4)) {
        stage.GetWoodBoxArray()[1]->SetEnable(false);
    }
    if (g_pInput->IsKeyPush(MOFKEY_5)) {
        stage.GetWoodBoxArray()[3]->SetEnable(false);
    }
    if (g_pInput->IsKeyPush(MOFKEY_6)) {
        stage.GetWoodBoxArray()[7]->SetEnable(false);
    }
    
    return TRUE;
}
/*************************************************************************//*!
        @brief            アプリケーションの描画
        @param            None

        @return            TRUE        成功<br>
                        それ以外    失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
    //描画開始
    g_pGraphics->RenderStart();

    //画面のクリア
    g_pGraphics->ClearTarget(0, 0, 0, 0, 1.0f, 0);
    
	CGraphicsUtilities::SetCamera(&main_camera);
    g_pGraphics->SetDepthEnable(TRUE);
    
    stage.Render();

    g_pGraphics->SetDepthEnable(FALSE);

    CMofImGui::RenderSetup();
    CMofImGui::RenderGui();

    //描画の終了
    g_pGraphics->RenderEnd();
    return TRUE;
}
/*************************************************************************//*!
        @brief            アプリケーションの解放
        @param            None

        @return            TRUE        成功<br>
                        それ以外    失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
    
    if (std::optional<std::string*> r = theParam.GetData<std::string>(ParamKey::ResourcePath)) {
        CUtilities::SetCurrentDirectory(r.value()->c_str());
    }

    CMofImGui::Cleanup();

    gamepad.Release();

    editor::EditorUtilities::SaveWindowParam();

    stage.Release();

    return TRUE;
}