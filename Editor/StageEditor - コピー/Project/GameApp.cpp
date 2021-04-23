/*************************************************************************//*!

                    @file    GameApp.cpp
                    @brief    ��{�Q�[���A�v���B

                                                            @author    �_�c�@��
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
        @brief            �A�v���P�[�V�����̏�����
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
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
        @brief            �A�v���P�[�V�����̍X�V
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
    CMofImGui::Refresh();
    //�L�[�̍X�V
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
        @brief            �A�v���P�[�V�����̕`��
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
    //�`��J�n
    g_pGraphics->RenderStart();

    //��ʂ̃N���A
    g_pGraphics->ClearTarget(0, 0, 0, 0, 1.0f, 0);
    
	CGraphicsUtilities::SetCamera(&main_camera);
    g_pGraphics->SetDepthEnable(TRUE);
    
    stage.Render();

    g_pGraphics->SetDepthEnable(FALSE);

    CMofImGui::RenderSetup();
    CMofImGui::RenderGui();

    //�`��̏I��
    g_pGraphics->RenderEnd();
    return TRUE;
}
/*************************************************************************//*!
        @brief            �A�v���P�[�V�����̉��
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
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