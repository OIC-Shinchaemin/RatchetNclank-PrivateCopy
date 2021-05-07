#include "SceneManager.h"

#include "SceneDefine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"


void my::SceneManager::ChangeScene(const std::string& name, std::shared_ptr<my::Scene::Param> param) {
    _scene.reset();
    if (name == my::SceneType::kTitleScene) {
        param->resource = "../Resource/scene_resource/title_scene.txt";
        auto temp = ut::MakeSharedWithRelease<my::TitleScene>();
        temp->SetResourceManager(_resource);
        _scene = temp;
    } // if
    else if (name == my::SceneType::kGameScene) {
        param->resource = "../Resource/scene_resource/game_scene.txt";
        auto temp = ut::MakeSharedWithRelease<my::GameScene>();
        temp->SetResourceManager(_resource);
        temp->SetUICanvas(_ui_canvas);
        temp->SetGameManager(_game_manager);
        _scene = temp;
    } // else if
    else if (name == my::SceneType::kClearScene) {
        param->resource = "../Resource/scene_resource/clear_scene.txt";
        auto temp = ut::MakeSharedWithRelease<my::ClearScene>();
        temp->SetResourceManager(_resource);
        _scene = temp;
    } // else if

    _scene->AddSceneObserver(shared_from_this());
    _scene->Load(param);
    _scene->Initialize();
}

void my::SceneManager::RenderScene(void) {
    _scene->Render();

    ::g_pGraphics->SetDepthEnable(false);
    if (auto canvas = _ui_canvas.lock()) {
        canvas->Render();
    } // if

}

my::SceneManager::SceneManager() :
    _change_message(),
    _resource(),
    _ui_canvas(),
    _game_manager() {
}

my::SceneManager::~SceneManager() {
}

void my::SceneManager::OnNotify(const SceneMessage& mesage) {
    _change_message = ChangeMessage();
    _change_message.value().name = mesage.type_name;
    if (mesage.info_name == "") {
        _change_message.value().param = std::make_shared <my::Scene::Param>();
    } // if
}

void my::SceneManager::SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr) {
    this->_resource = ptr;
}

void my::SceneManager::SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr) {
    this->_ui_canvas = ptr;
}

void my::SceneManager::SetGameManager(std::weak_ptr<my::GameManager> ptr) {
    this->_game_manager = ptr;
}

bool my::SceneManager::Initialize(void) {
    this->ChangeScene(my::SceneType::kTitleScene, std::make_shared <my::Scene::Param>());

    return true;
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
