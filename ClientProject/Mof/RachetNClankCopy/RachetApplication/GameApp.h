#pragma once

#include "Mof.h"
#include "Game/GameManager.h"
#include "Camera/CameraManager.h"


class CGameApp : public CSingleGameApplication {
private:
	//! �Q�[��
	std::shared_ptr<my::GameManager> _game_manager;
	//! �J����
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
