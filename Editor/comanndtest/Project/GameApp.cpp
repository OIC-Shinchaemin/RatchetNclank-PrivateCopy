/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"CommandManager.h"

CCamera        main_camera;

CSphere        sphere(Vector3(), 1);
CommandManager cmdManager;
ICommandPtr    nowCommand;

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
	main_camera.LookAt(Vector3(0, 2, -3), Vector3(), Vector3(0, 1, 0));
	main_camera.Update();
	CGraphicsUtilities::SetCamera(&main_camera);

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

	if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {
		cmdManager.Register(
			std::make_shared<MoveCommand>(Vector3(-0.01f, 0, 0), &sphere)
		);
	}
	if (g_pInput->IsKeyPush(MOFKEY_RIGHT)) {
		nowCommand = std::make_shared<PositionCommand>(&sphere);
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
		sphere.Translation(Vector3(0.01f, 0, 0));
	}
	if (g_pInput->IsKeyPull(MOFKEY_RIGHT)) {
		nowCommand->Register();
		cmdManager.Register(nowCommand);
		nowCommand = nullptr;
	}
	if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) && g_pInput->IsKeyPush(MOFKEY_Z)) {
		cmdManager.Undo();
	}
	if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) && g_pInput->IsKeyPush(MOFKEY_Y)) {
		cmdManager.Redo();
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

	CGraphicsUtilities::RenderSphere(sphere, Vector4(0, 1, 0, 1));

	g_pGraphics->SetDepthEnable(FALSE);

	const std::vector<ICommandPtr>& execs = cmdManager.GetExecArray();
	const std::vector<ICommandPtr>& redos = cmdManager.GetRedoArray();
	int offset_y = 0;
	for (const auto& it : execs) {
		CGraphicsUtilities::RenderString(0, offset_y, it->GetName().c_str());
		offset_y += 30;
	}
	offset_y = 0;
	for (const auto& it : redos) {
		CGraphicsUtilities::RenderString(300, offset_y, it->GetName().c_str());
		offset_y += 30;
	}

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
	return TRUE;
}