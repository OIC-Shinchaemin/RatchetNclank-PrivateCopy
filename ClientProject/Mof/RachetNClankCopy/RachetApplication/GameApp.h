#pragma once

#include "Mof.h"
#include "ResourceManager.h"
//#include "Factory/FactoryManager.h"
#include "Game/GameManager.h"
#include "Camera/CameraManager.h"
#include "My/UI/UICanvas.h"


class CGameApp : public CSingleGameApplication {
private:
	//! リソース
	std::shared_ptr<my::ResourceMgr> _resource_manager;
	//! ファクトリー
	//std::shared_ptr<my::FactoryManager> _factory_manager;
	//! ゲーム
	std::shared_ptr<my::GameManager> _game_manager;
	//! カメラ
	std::shared_ptr<my::CameraManager> _camera_manager;
	//! カメラ
	std::shared_ptr<my::UICanvas> _ui_canvas;
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
