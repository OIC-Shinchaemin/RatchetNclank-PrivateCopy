/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "Stage.h"

Stage          stage;

CCamera        main_camera;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	
	const float width  = g_pGraphics->GetTargetWidth();
	const float height = g_pGraphics->GetTargetHeight();
	
	main_camera.SetViewPort();
	main_camera.PerspectiveFov(MOF_ToRadian(60.0f), width / height, 0.01f, 1000.0f);
	main_camera.LookAt(Vector3(0, 10, -30), Vector3(), Vector3(0, 1, 0));
	main_camera.Update();
	CGraphicsUtilities::SetCamera(&main_camera);

	stage.Load("test.json");
	stage.Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

	stage.Update();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	g_pGraphics->SetDepthEnable(TRUE);

	stage.Render();
	/*MeshPtr mesh = stage.GetStaticStageMesh();
	if (mesh) {
		CMatrix44 mat;
		mesh->Render(mat);
	}*/
	g_pGraphics->SetDepthEnable(FALSE);

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {

	stage.Release();

	return TRUE;
}