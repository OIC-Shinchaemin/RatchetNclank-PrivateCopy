/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "Stage.h"

Stage          stage;

CCamera        main_camera;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	
	const float width  = g_pGraphics->GetTargetWidth();
	const float height = g_pGraphics->GetTargetHeight();
	
	main_camera.SetViewPort();
	main_camera.PerspectiveFov(MOF_ToRadian(60.0f), width / height, 0.01f, 1000.0f);
	//main_camera.LookAt(Vector3(50, 30, -50), Vector3(), Vector3(0, 1, 0));
	main_camera.LookAt(Vector3(0, 10, -30), Vector3(), Vector3(0, 1, 0));
	main_camera.Update();
	CGraphicsUtilities::SetCamera(&main_camera);

	stage.Load("test.json");
	stage.Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	stage.Update(0.016667f);

	if (g_pInput->IsKeyPush(MOFKEY_1)) {
		stage.Initialize();
	}
	if (g_pInput->IsKeyPush(MOFKEY_2)) {
		stage.GetGimmickArray()[0]->ActionStart();
	}
	if (g_pInput->IsKeyPush(MOFKEY_3)) {
		stage.GetGimmickArray()[1]->ActionStart();
	}
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
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	g_pGraphics->SetDepthEnable(TRUE);

	stage.Render();

	g_pGraphics->SetDepthEnable(FALSE);

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {

	stage.Release();

	return TRUE;
}