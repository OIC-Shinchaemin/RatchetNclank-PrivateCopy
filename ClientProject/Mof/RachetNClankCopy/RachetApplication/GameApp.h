#pragma once

#include "Mof.h"
#include "Game/GameManager.h"
#include "Camera/CameraManager.h"


class CGameApp : public CSingleGameApplication {
private:
	//! ÉQÅ[ÉÄ
	std::shared_ptr<my::GameManager> _game_manager;
	//! ÉJÉÅÉâ
	std::shared_ptr<my::CameraManager> _camera_manager;

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
