#include "SceneManager.h"

#include "SceneDefine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "DescriptionScene.h"
#include "../Factory/Builder/Scene/SceneBuilder.h"
#include "../Factory/Builder/Scene/GameSceneBuilder.h"


void my::SceneManager::ChangeScene(const std::string& name, std::shared_ptr<my::Scene::Param> param) {
    auto& [factory, builders, reousrce_paths] = _create_struct;

    _scene.reset();
    _scene = factory.Create(name);
    builders.at(name)->Construct(_scene);
    param->resource = reousrce_paths.at(name);

    _scene->AddSceneObserver(shared_from_this());
    _scene->Load(param);
    _scene->Initialize();
}

void my::SceneManager::RenderScene(void) {
    _scene->Render();

    ::g_pGraphics->SetDepthEnable(false);
    if (auto canvas = _managers.ui_canvas.lock()) {
        canvas->Render();
    } // if

}

my::SceneManager::SceneManager() :
    _change_message(),
    _managers(),
    _create_struct(){
    auto& [factory, builders, reousrce_paths] = _create_struct;

    factory.Register<my::TitleScene>(my::SceneType::kTitleScene);
    factory.Register<my::GameScene>(my::SceneType::kGameScene);
    factory.Register<my::ClearScene>(my::SceneType::kClearScene);
    factory.Register<my::DescriptionScene>(my::SceneType::kDescriptionScene);

    reousrce_paths.emplace(my::SceneType::kTitleScene, my::scene::ResourcePath::kTitleScene);
    reousrce_paths.emplace(my::SceneType::kGameScene, my::scene::ResourcePath::kGameScene);
    reousrce_paths.emplace(my::SceneType::kClearScene, my::scene::ResourcePath::kClearScene);
    reousrce_paths.emplace(my::SceneType::kDescriptionScene, my::scene::ResourcePath::kDescriptionScene);
}

my::SceneManager::~SceneManager() {
}

void my::SceneManager::OnNotify(const scene::SceneMessage& mesage) {
    _change_message = ChangeMessage();
    _change_message.value().name = mesage.type_name;
    if (mesage.info_name == "") {
        _change_message.value().param = std::make_shared <my::Scene::Param>();
    } // if
}

void my::SceneManager::SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr) {
    this->_managers.resource = ptr;
}

void my::SceneManager::SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr) {
    this->_managers.ui_canvas = ptr;
}

void my::SceneManager::SetGameManager(std::weak_ptr<my::GameManager> ptr) {
    this->_managers.game_manager = ptr;
}

void my::SceneManager::SetEventManager(std::weak_ptr<my::EventManager> ptr) {
    this->_managers.event_manager = ptr;
}

bool my::SceneManager::Initialize(void) {
    this->RegisterBuilder<builder::TitleSceneBuilder>(my::SceneType::kTitleScene);
    this->RegisterBuilder<builder::SceneBuilder>(my::SceneType::kDescriptionScene);
    this->RegisterBuilder<builder::SceneBuilder>(my::SceneType::kClearScene);
    this->RegisterBuilder<builder::GameSceneBuilder>(my::SceneType::kGameScene);


    this->ChangeScene(my::SceneType::kTitleScene, std::make_shared <my::Scene::Param>());
    return true;
}

bool my::SceneManager::Input(void) {
    return _scene->Input();
}

bool my::SceneManager::Update(float delta_time) {
    if (_change_message.has_value()) {
        this->ChangeScene(_change_message.value().name, _change_message.value().param);
        _change_message.reset();
    } // if

    _scene->Update(delta_time);
    return true;
}

bool my::SceneManager::Render(void) {
    this->RenderScene();
    return true;
}

bool my::SceneManager::Release(void) {
    _scene.reset();
    return true;
}
