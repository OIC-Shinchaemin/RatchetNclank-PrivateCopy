#include "SceneManager.h"

#include "SceneDefine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "DescriptionScene.h"
#include "../Factory/Builder/Scene/SceneBuilder.h"
#include "../Factory/Builder/Scene/GameSceneBuilder.h"


void ratchet::scene::SceneManager::ChangeScene(const std::string& name, std::shared_ptr<ratchet::scene::Scene::Param> param) {
	auto& [factory, builders, reousrce_paths] = _create_struct;

	_scene->Release();
	_scene.reset();
	_scene = factory.Create(name);
	builders.at(name)->Construct(_scene);
	param->resource = reousrce_paths.at(name);

	_scene->AddSceneObserver(shared_from_this());
	_scene->Load(param);
	_scene->Initialize();
}

void ratchet::scene::SceneManager::RenderScene(void) {
	_scene->Render();

	::g_pGraphics->SetDepthEnable(false);
	if (auto canvas = _managers.ui_canvas.lock()) {
		canvas->Render();
	} // if

}

ratchet::scene::SceneManager::SceneManager() :
	_change_message(),
	_managers(),
	_create_struct() {
	auto& [factory, builders, reousrce_paths] = _create_struct;

	factory.Register<ratchet::scene::TitleScene>(ratchet::scene::SceneType::kTitleScene);
	factory.Register<ratchet::scene::GameScene>(ratchet::scene::SceneType::kGameScene);
	factory.Register<ratchet::scene::ClearScene>(ratchet::scene::SceneType::kClearScene);
	factory.Register<ratchet::scene::DescriptionScene>(ratchet::scene::SceneType::kDescriptionScene);

	reousrce_paths.emplace(ratchet::scene::SceneType::kTitleScene, ratchet::scene::ResourcePath::kTitleScene);
	reousrce_paths.emplace(ratchet::scene::SceneType::kGameScene, ratchet::scene::ResourcePath::kGameScene);
	reousrce_paths.emplace(ratchet::scene::SceneType::kClearScene, ratchet::scene::ResourcePath::kClearScene);
	reousrce_paths.emplace(ratchet::scene::SceneType::kDescriptionScene, ratchet::scene::ResourcePath::kDescriptionScene);
}

ratchet::scene::SceneManager::~SceneManager() {
}

void ratchet::scene::SceneManager::OnNotify(const scene::SceneMessage& mesage) {
	_change_message = ChangeMessage();
	_change_message.value().name = mesage.type_name;
	if (mesage.info_name == "") {
		_change_message.value().param = std::make_shared <ratchet::scene::Scene::Param>();
	} // if
}

void ratchet::scene::SceneManager::SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
	this->_managers.resource = ptr;
}

void ratchet::scene::SceneManager::SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr) {
	this->_managers.ui_canvas = ptr;
}

void ratchet::scene::SceneManager::SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr) {
	this->_managers.game_manager = ptr;
}

void ratchet::scene::SceneManager::SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr) {
	this->_managers.event_manager = ptr;
}

void ratchet::scene::SceneManager::SetLightManager(std::weak_ptr<ratchet::light::LightManager> ptr) {
	this->_managers.light_manager  = ptr;
}

bool ratchet::scene::SceneManager::Initialize(void) {
	this->RegisterBuilder<ratchet::factory::builder::scene::TitleSceneBuilder>(ratchet::scene::SceneType::kTitleScene);
	this->RegisterBuilder<ratchet::factory::builder::scene::SceneBuilder>(ratchet::scene::SceneType::kDescriptionScene);
	this->RegisterBuilder<ratchet::factory::builder::scene::SceneBuilder>(ratchet::scene::SceneType::kClearScene);
	this->RegisterBuilder<ratchet::factory::builder::scene::GameSceneBuilder>(ratchet::scene::SceneType::kGameScene);

	this->ChangeScene(ratchet::scene::SceneType::kTitleScene, std::make_shared <ratchet::scene::Scene::Param>());
	return true;
}

bool ratchet::scene::SceneManager::Input(void) {
	auto state = _scene->GetState();
	if (state != decltype(state)::Sleep) {
		return _scene->Input();
	} // if
	return false;
}

bool ratchet::scene::SceneManager::Update(float delta_time) {
	if (_change_message.has_value()) {
		this->ChangeScene(_change_message.value().name, _change_message.value().param);
		_change_message.reset();
	} // if

	_scene->Update(delta_time);
	return true;
}

bool ratchet::scene::SceneManager::Render(void) {
	this->RenderScene();
	return true;
}

bool ratchet::scene::SceneManager::Release(void) {
	_scene->Release();
	_scene.reset();
	return true;
}
