#include "GameApp.h"

#include "Gamepad.h"
#include "Base/Core/Define.h"

#include "Factory/FactoryManager.h"
#include "Component/Component.h"
#include "Camera/CameraController.h"
#include "DebugManager.h"
#include "TutorialManager.h"


MofBool CGameApp::Initialize(void) {
	::CUtilities::SetCurrentDirectory("Resource");

	ratchet::Gamepad::GetInstance().Create();
	_resource_manager = ut::MakeSharedWithRelease<ratchet::ResourceMgr>();
	_camera_manager = std::make_shared<ratchet::camera::CameraManager>();
	_light_manager = std::make_shared<ratchet::light::LightManager>();
	_game_manager = ut::MakeSharedWithRelease<ratchet::game::GameManager>();
	_event_manager = ut::MakeSharedWithRelease<ratchet::event::EventManager>();
	_ui_canvas = std::make_shared<base::ui::UICanvas>();
	_scene_manager = ut::MakeSharedWithRelease<ratchet::scene::SceneManager>();

	ratchet::factory::FactoryManager::Singleton().SetResourceManager(_resource_manager);
	ratchet::factory::FactoryManager::Singleton().SetGameManager(_game_manager);
	ratchet::component::Component::SetResourceManager(_resource_manager);
	ratchet::component::Component::SetUICanvas(_ui_canvas);
	ratchet::camera::CameraController::SetCameraManager(_camera_manager);

	_light_manager->Initialize();

	_game_manager->SetResourceManager(_resource_manager);
	_game_manager->SetUICanvas(_ui_canvas);
	_game_manager->Initialize();

	_scene_manager->SetResourceManager(_resource_manager);
	_scene_manager->SetGameManager(_game_manager);
	_scene_manager->SetEventManager(_event_manager);
	_scene_manager->SetUICanvas(_ui_canvas);
	_scene_manager->Initialize();
	return TRUE;
}

MofBool CGameApp::Input(void) {
	::g_pInput->RefreshKey();
	::g_pGamepad->RefreshKey();

	if (::g_pInput->IsKeyPush(MOFKEY_F1)) {
		debug::DebugManager::GetInstance().ChangeDebugMode();
	} // if

	if (::g_pInput->IsKeyPush(MOFKEY_F6)) {
		tutorial::TutorialManager::GetInstance().Liberation(tutorial::TutorialManager::TutorialType::Jump);
	} // if
	if (::g_pInput->IsKeyPush(MOFKEY_F7)) {
		tutorial::TutorialManager::GetInstance().Liberation(tutorial::TutorialManager::TutorialType::Attack);
	} // if
	return TRUE;
}

MofBool CGameApp::Update(void) {
	this->Input();

	float delta_time = 0.01667f;

	_scene_manager->Input();

	_event_manager->Update(delta_time);
	_game_manager->Update(delta_time);
	_scene_manager->Update(delta_time);
	_camera_manager->Update();
	_ui_canvas->Update(delta_time);
	return TRUE;
}

MofBool CGameApp::Render(void) {
	::g_pGraphics->RenderStart();

	_scene_manager->Render();

	if (debug::DebugManager::GetInstance().IsDebugMode()) {
		auto fps = ::CUtilities::GetFPS();
		::CGraphicsUtilities::RenderString(10.0f, 10.0f, "fps = %d", fps);
		
		if (tutorial::TutorialManager::GetInstance().IsLiberation(tutorial::TutorialManager::TutorialType::Jump)) {
			::CGraphicsUtilities::RenderString(10.0f, 60.0f, "jump tutorial flag = true");
		} // if
		else {
			::CGraphicsUtilities::RenderString(10.0f, 60.0f, "jump tutorial flag = false");
		} // else


		if (tutorial::TutorialManager::GetInstance().IsLiberation(tutorial::TutorialManager::TutorialType::Attack)) {
			::CGraphicsUtilities::RenderString(10.0f, 90.0f, "attack tutorial flag = true");
		} // if
		else {
			::CGraphicsUtilities::RenderString(10.0f, 90.0f, "attack tutorial flag = false");
		} // else
	} // if
	::g_pGraphics->RenderEnd();
	return TRUE;
}

MofBool CGameApp::Release(void) {
	_scene_manager.reset();
	_ui_canvas.reset();
	_event_manager.reset();
	_game_manager.reset();
	_light_manager.reset();
	_camera_manager.reset();
	_resource_manager.reset();
	ratchet::Gamepad::GetInstance().Release();
	return TRUE;
}