#pragma once

#include "Mof.h"
#include "CameraManager.h"


class CGameApp : public CSingleGameApplication {
private:
	//! ÉJÉÅÉâ
	std::shared_ptr<my::CameraManager> _camera_manager;

	void InitializeGame(void);
	void UpdateGame(float delta);
	void UpdateUI(float delta);
	void UpdateCamera(float delta);
	void RenderScene(void);
	void Render3D(void);
	void Render2D(void);
public:
	CGameApp(){}
	virtual ~CGameApp(){	Release();	}
	virtual MofBool Initialize(void);
	virtual MofBool Input(void);
	virtual MofBool Update(void);
	virtual MofBool Render(void);
	virtual MofBool Release(void);
};
