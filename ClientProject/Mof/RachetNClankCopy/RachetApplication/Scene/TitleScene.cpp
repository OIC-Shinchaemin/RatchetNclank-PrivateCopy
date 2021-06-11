#include "TitleScene.h"
#include "../Gamepad.h"
#include "Base/Resource/ResourceFont.h"
#include "../Factory/FactoryManager.h"
#include "../Camera/FollowCameraController.h"


bool rachet::TitleScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_SPACE) || ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _option_system_subject.Notify(true);
    } // if


    _demo_actor->Update(delta_time);

    auto camera_info = rachet::CameraController::CameraInfo();

    auto pos = Mof::CVector3(10.0f, -2.0f, -15.0f);
    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(_camera_controller.GetService()->GetAzimuth()) + 0.2f);
    //_camera_controller.GetService()->SetCameraTarget(pos);
    camera_info.target_position = pos;
    _camera_controller.GetService()->Update(delta_time, camera_info);
    return true;
}

bool rachet::TitleScene::LoadingUpdate(float delta_time) {
    return true;
}

bool rachet::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);

    _demo_actor->Render();
    _stage.Render();
    ::g_pGraphics->SetDepthEnable(false);
    return true;
}

bool rachet::TitleScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);
    ::CGraphicsUtilities::RenderString(800.0f, 700.0f, def::color_rgba_u32::kWhite, "Now Loading...");
    return true;
}

rachet::TitleScene::TitleScene() :
    super(),
    _stage(),
    _stage_view_camera(),
    _camera_controller(),
    _demo_actor(),
    _game(),
    _ui_creator("TitleInfoMenu") {
}

rachet::TitleScene::~TitleScene() {
    _game.reset();
}

void rachet::TitleScene::OnNotify(const char* type, const std::shared_ptr<rachet::Actor>& ptr) {
}

void rachet::TitleScene::OnNotify(const rachet::OptionSystem::Info& info) {
    if (info.enter) {
        this->_state = super::State::Pause;
    } // if
    if (info.exit) {
        this->_state = super::State::Active;
    } // if
}

void rachet::TitleScene::SetGameManager(std::weak_ptr<rachet::GameManager> ptr) {
    this->_game = ptr;
}

std::string rachet::TitleScene::GetName(void) {
    return rachet::SceneType::kTitleScene;
}

bool rachet::TitleScene::Load(std::shared_ptr<rachet::Scene::Param> param) {
    super::Load(param);

    super::_load_thread = std::thread([&]() {
        if (!super::IsLoaded()) {
            auto re = ::CoInitialize(NULL);
            auto path = "../Resource/scene_resource/game_scene.txt";
            if (auto r = _resource.lock()) {
                r->Load(path);
            } // if
            // stage
            if (!_stage.Load("../Resource/stage/test.json")) {
            } // if
            _stage.Initialize();

            auto actor_param = rachet::Actor::Param();
            actor_param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
            actor_param.transform.position = Mof::CVector3(10.0f, -5.0f, -15.0f);
            _demo_actor = rachet::FactoryManager::Singleton().CreateActor<rachet::Player>("builder/demo_player.json", &actor_param);

            ::CoUninitialize();
            super::LoadComplete();

            // camera
            _stage_view_camera = (std::make_shared<rachet::Camera>());
            auto pos = math::vec3::kZero;
            auto offset = math::vec3::kNegUnitZ;
            _stage_view_camera->SetPosition(pos - offset);
            _stage_view_camera->SetTarget(pos);
            _stage_view_camera->Initialize();
            _stage_view_camera->Update();
            _camera_controller.SetService(std::make_shared<rachet::FollowCameraController>());
            _camera_controller.GetService()->SetCamera(_stage_view_camera);
            _camera_controller.GetService()->RegisterGlobalCamera();
            _camera_controller.GetService()->SetAzimuth(0.0f);
            _camera_controller.GetService()->SetAltitude(-10.0f);
            _camera_controller.GetService()->SetDistance(8.0f);
        } // if


        auto menu = _ui_creator.Create(super::GetUICanvas());
        menu->SetResourceManager(super::GetResource());
        _title_menu_subject.AddObserver(menu);
        _title_menu_subject.Notify(true);


        if (auto game = _game.lock()) {
            auto option_system = game->GetOptionSystem();

            _option_system_subject.AddObserver(option_system);
            option_system->GetTitleMenuSubject()->AddObserver(menu);

            auto item0 = std::make_shared<rachet::OptionSystemItem>([&]() {
                _subject.Notify(scene::SceneMessage(rachet::SceneType::kDescriptionScene, ""));
                return true;
            });
            item0->SetText("操作説明");

            auto item1 = std::make_shared<rachet::OptionSystemItem>([&]() {
                _subject.Notify(scene::SceneMessage(rachet::SceneType::kGameScene, ""));
                return true;
            });
            item1->SetText("ゲームスタート");
            option_system->Initialize();
            option_system->AddItem(item1);
            option_system->AddItem(item0);
        } // if

    });


    return true;
}

bool rachet::TitleScene::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::TitleScene::Release(void) {
    super::Release();
    if (auto game = _game.lock()) {
        game->GetOptionSystem()->Release();
        _option_system_subject.Clear();
        _title_menu_subject.Clear();
    } // if

    _stage.Release();
    return true;
}