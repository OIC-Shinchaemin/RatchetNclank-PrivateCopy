#include "SceneManager.h"

#include "SceneDefine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "DescriptionScene.h"
#include "../Factory/Builder/Scene/SceneBuilder.h"
#include "../Factory/Builder/Scene/GameSceneBuilder.h"


void rachet::SceneManager::ChangeScene(const std::string& name, std::shared_ptr<rachet::Scene::Param> param) {
    auto& [factory, builders, reousrce_paths] = _create_struct;

    _scene.reset();
    _scene = factory.Create(name);
    builders.at(name)->Construct(_scene);
    param->resource = reousrce_paths.at(name);

    _scene->AddSceneObserver(shared_from_this());
    _scene->Load(param);
    _scene->Initialize();
}

void rachet::SceneManager::RenderScene(void) {
    _scene->Render();

    ::g_pGraphics->SetDepthEnable(false);
    if (auto canvas = _managers.ui_canvas.lock()) {
        canvas->Render();
    } // if

}

rachet::SceneManager::SceneManager() :
    _change_message(),
    _managers(),
    _create_struct(){
    auto& [factory, builders, reousrce_paths] = _create_struct;

    factory.Register<rachet::TitleScene>(rachet::SceneType::kTitleScene);
    factory.Register<rachet::GameScene>(rachet::SceneType::kGameScene);
    factory.Register<rachet::ClearScene>(rachet::SceneType::kClearScene);
    factory.Register<rachet::DescriptionScene>(rachet::SceneType::kDescriptionScene);

    reousrce_paths.emplace(rachet::SceneType::kTitleScene, rachet::scene::ResourcePath::kTitleScene);
    reousrce_paths.emplace(rachet::SceneType::kGameScene, rachet::scene::ResourcePath::kGameScene);
    reousrce_paths.emplace(rachet::SceneType::kClearScene, rachet::scene::ResourcePath::kClearScene);
    reousrce_paths.emplace(rachet::SceneType::kDescriptionScene, rachet::scene::ResourcePath::kDescriptionScene);
}

rachet::SceneManager::~SceneManager() {
}

void rachet::SceneManager::OnNotify(const scene::SceneMessage& mesage) {
    _change_message = ChangeMessage();
    _change_message.value().name = mesage.type_name;
    if (mesage.info_name == "") {
        _change_message.value().param = std::make_shared <rachet::Scene::Param>();
    } // if
}

void rachet::SceneManager::SetResourceManager(const std::shared_ptr<rachet::ResourceMgr>& ptr) {
    this->_managers.resource = ptr;
}

void rachet::SceneManager::SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr) {
    this->_managers.ui_canvas = ptr;
}

void rachet::SceneManager::SetGameManager(std::weak_ptr<rachet::GameManager> ptr) {
    this->_managers.game_manager = ptr;
}

void rachet::SceneManager::SetEventManager(std::weak_ptr<rachet::EventManager> ptr) {
    this->_managers.event_manager = ptr;
}

bool rachet::SceneManager::Initialize(void) {
    this->RegisterBuilder<builder::TitleSceneBuilder>(rachet::SceneType::kTitleScene);
    this->RegisterBuilder<builder::SceneBuilder>(rachet::SceneType::kDescriptionScene);
    this->RegisterBuilder<builder::SceneBuilder>(rachet::SceneType::kClearScene);
    this->RegisterBuilder<builder::GameSceneBuilder>(rachet::SceneType::kGameScene);


    this->ChangeScene(rachet::SceneType::kTitleScene, std::make_shared <rachet::Scene::Param>());
    return true;
}

bool rachet::SceneManager::Input(void) {
    return _scene->Input();
}

bool rachet::SceneManager::Update(float delta_time) {
    if (_change_message.has_value()) {
        this->ChangeScene(_change_message.value().name, _change_message.value().param);
        _change_message.reset();
    } // if

    _scene->Update(delta_time);
    return true;
}

bool rachet::SceneManager::Render(void) {
    this->RenderScene();
    return true;
}

bool rachet::SceneManager::Release(void) {
    _scene.reset();
    return true;
}
