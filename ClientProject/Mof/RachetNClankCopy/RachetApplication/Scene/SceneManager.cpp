#include "SceneManager.h"

#include "SceneDefine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "DescriptionScene.h"
#include "../Factory/Builder/Scene/SceneBuilder.h"
#include "../Factory/Builder/Scene/GameSceneBuilder.h"


void ratchet::SceneManager::ChangeScene(const std::string& name, std::shared_ptr<ratchet::Scene::Param> param) {
    auto& [factory, builders, reousrce_paths] = _create_struct;

    _scene.reset();
    _scene = factory.Create(name);
    builders.at(name)->Construct(_scene);
    param->resource = reousrce_paths.at(name);

    _scene->AddSceneObserver(shared_from_this());
    _scene->Load(param);
    _scene->Initialize();
}

void ratchet::SceneManager::RenderScene(void) {
    _scene->Render();

    ::g_pGraphics->SetDepthEnable(false);
    if (auto canvas = _managers.ui_canvas.lock()) {
        canvas->Render();
    } // if

}

ratchet::SceneManager::SceneManager() :
    _change_message(),
    _managers(),
    _create_struct(){
    auto& [factory, builders, reousrce_paths] = _create_struct;

    factory.Register<ratchet::TitleScene>(ratchet::SceneType::kTitleScene);
    factory.Register<ratchet::GameScene>(ratchet::SceneType::kGameScene);
    factory.Register<ratchet::ClearScene>(ratchet::SceneType::kClearScene);
    factory.Register<ratchet::DescriptionScene>(ratchet::SceneType::kDescriptionScene);

    reousrce_paths.emplace(ratchet::SceneType::kTitleScene, ratchet::scene::ResourcePath::kTitleScene);
    reousrce_paths.emplace(ratchet::SceneType::kGameScene, ratchet::scene::ResourcePath::kGameScene);
    reousrce_paths.emplace(ratchet::SceneType::kClearScene, ratchet::scene::ResourcePath::kClearScene);
    reousrce_paths.emplace(ratchet::SceneType::kDescriptionScene, ratchet::scene::ResourcePath::kDescriptionScene);
}

ratchet::SceneManager::~SceneManager() {
}

void ratchet::SceneManager::OnNotify(const scene::SceneMessage& mesage) {
    _change_message = ChangeMessage();
    _change_message.value().name = mesage.type_name;
    if (mesage.info_name == "") {
        _change_message.value().param = std::make_shared <ratchet::Scene::Param>();
    } // if
}

void ratchet::SceneManager::SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
    this->_managers.resource = ptr;
}

void ratchet::SceneManager::SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr) {
    this->_managers.ui_canvas = ptr;
}

void ratchet::SceneManager::SetGameManager(std::weak_ptr<ratchet::GameManager> ptr) {
    this->_managers.game_manager = ptr;
}

void ratchet::SceneManager::SetEventManager(std::weak_ptr<ratchet::EventManager> ptr) {
    this->_managers.event_manager = ptr;
}

bool ratchet::SceneManager::Initialize(void) {
    this->RegisterBuilder<builder::TitleSceneBuilder>(ratchet::SceneType::kTitleScene);
    this->RegisterBuilder<builder::SceneBuilder>(ratchet::SceneType::kDescriptionScene);
    this->RegisterBuilder<builder::SceneBuilder>(ratchet::SceneType::kClearScene);
    this->RegisterBuilder<builder::GameSceneBuilder>(ratchet::SceneType::kGameScene);


    this->ChangeScene(ratchet::SceneType::kTitleScene, std::make_shared <ratchet::Scene::Param>());
    return true;
}

bool ratchet::SceneManager::Input(void) {
    return _scene->Input();
}

bool ratchet::SceneManager::Update(float delta_time) {
    if (_change_message.has_value()) {
        this->ChangeScene(_change_message.value().name, _change_message.value().param);
        _change_message.reset();
    } // if

    _scene->Update(delta_time);
    return true;
}

bool ratchet::SceneManager::Render(void) {
    this->RenderScene();
    return true;
}

bool ratchet::SceneManager::Release(void) {
    _scene.reset();
    return true;
}
