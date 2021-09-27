#include "TitleScene.h"
#include "../Gamepad.h"
#include "Base/Resource/ResourceFont.h"
#include "../Factory/FactoryManager.h"
#include "../Camera/FollowCameraController.h"


void ratchet::scene::TitleScene::FadeOutStart(void) {
    if (_scene_end) {
        return;
    } // if
    _effect = ratchet::scene::SceneEffect();
    _effect.value().Load("../Resource/shader/fadeout.hlsl");
    bool seccess = _effect.value().CreateShaderBuffer("cbSceneEffectParam", sizeof(ratchet::scene::cbSceneEffectParam));
    _effect.value().time = 1.0f;
    _transition_state = TransitionState::Out;
    _scene_end = true;
}

bool ratchet::scene::TitleScene::SceneUpdate(float delta_time) {
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        ::PostQuitMessage(0);
        return false;
    } // if

    if (_input_flag) {
        if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
            ::g_pInput->IsKeyPush(MOFKEY_SPACE) || ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
            _option_system_subject.Notify(true);
        } // if
    } // if

    if (_input_timer.Tick(delta_time)) {
        _input_flag = true;
    } // if
    

    bool effect_end = super::SceneUpdate(delta_time);
    if (effect_end && _transition_state == TransitionState::End) {
        _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kGameScene, ""));
    } // if

    _demo_actor->Update(delta_time);

    auto camera_info = ratchet::camera::CameraController::CameraInfo();

    auto pos = Mof::CVector3(10.0f, -2.0f, -15.0f);
    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(_camera_controller.GetService()->GetAzimuth()) + 0.2f);
    camera_info.target_position = pos;
    _camera_controller.GetService()->Update(delta_time, camera_info);

    _logo.Update(delta_time);
    _bgm.Update();
    if (_scene_end) {
        _bgm.SetVolume(_bgm.GetVolume() * 0.9f);
    } // if
    return true;
}

bool ratchet::scene::TitleScene::LoadingUpdate(float delta_time) {
    if (_loading_counter.Tick(delta_time)) {
        _loading_dot_count++;
        int count_max = 4;
        _loading_dot_count = std::clamp(_loading_dot_count, 0, count_max);
        if (_loading_dot_count == count_max) {
            _loading_dot_count = 0;
        } // if
    } // if
    return true;
}

bool ratchet::scene::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);

    _demo_actor->Render();
    _stage.Render();
    ::g_pGraphics->SetDepthEnable(false);

    _logo.Render();
    return true;
}

bool ratchet::scene::TitleScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);
    auto text = std::string("Now Loading");
    for (int i = 0; i < _loading_dot_count; i++) {
        text += ".";
    } // for
    ::CGraphicsUtilities::RenderString(800.0f, 700.0f, def::color_rgba_u32::kWhite, text.c_str());
    return true;
}

ratchet::scene::TitleScene::TitleScene() :
    super(),
    _stage(),
    _stage_view_camera(),
    _camera_controller(),
    _demo_actor(),
    _game(),
    _ui_creator("TitleInfoMenu"),
    _scene_end(false),
    _loading_counter(),
    _loading_dot_count(0),
    _input_flag(false),
    _input_timer(),
    _bgm(){
    _loading_counter.Initialize(1.0f, true);
    _input_timer.Initialize(2.0f, false);
}

ratchet::scene::TitleScene::~TitleScene() {
    _game.reset();
}

void ratchet::scene::TitleScene::OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) {
}

void ratchet::scene::TitleScene::OnNotify(const ratchet::game::gamesystem::OptionSystem::Info& info) {
    if (info.enter) {
        this->_state = super::State::Pause;
    } // if
    if (info.exit) {
        this->_state = super::State::Active;
    } // if
}

void ratchet::scene::TitleScene::SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr) {
    this->_game = ptr;
}

std::string ratchet::scene::TitleScene::GetName(void) {
    return ratchet::scene::SceneType::kTitleScene;
}

bool ratchet::scene::TitleScene::Load(std::shared_ptr<ratchet::scene::Scene::Param> param) {
    super::Load(param);
    //	_ASSERT_EXPR(loaded, L"読み込み失敗");

    // shader
    auto effect = SceneEffect();
    effect.Load("../Resource/shader/fadein.hlsl");
    effect.CreateShaderBuffer("cbSceneEffectParam", sizeof(ratchet::cbSceneEffectParam));
    //super::_effect = effect;

    super::_load_thread = std::thread([&]() {
        if (!super::IsLoaded()) {
            auto re = ::CoInitialize(NULL);
            auto path = "../Resource/scene_resource/game_scene.txt";
            if (auto r = _resource.lock()) {
                r->Load(path);
            } // if
            _bgm.Load("bgm/title.mp3");
            _bgm.SetLoop(true);
            //_bgm.SetVolume(0.5f);
            _bgm.SetVolume(0.0f);

            _logo.SetTexture(super::GetResource()->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/title_logo/image.png"));

            // stage
            if (!_stage.Load("../Resource/stage/test.json")) {
            } // if
            _stage.Initialize();

            auto actor_param = ratchet::actor::Actor::Param();
            actor_param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
            actor_param.transform.position = Mof::CVector3(10.0f, -5.0f, -15.0f);
            _demo_actor = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Player>("builder/demo_player.json", &actor_param);

            ::CoUninitialize();
            super::LoadComplete();

            // camera
            _stage_view_camera = (std::make_shared<ratchet::camera::Camera>());
            //////////////auto pos = math::vec3::kZero;
            auto pos = actor_param.transform.position;
            auto offset = math::vec3::kNegUnitZ;
            _stage_view_camera->SetPosition(pos - offset);
            _stage_view_camera->SetTarget(pos);
            _stage_view_camera->Initialize();
            _stage_view_camera->Update();
            _camera_controller.SetService(std::make_shared<ratchet::camera::FollowCameraController>());
            _camera_controller.GetService()->SetCamera(_stage_view_camera);
            _camera_controller.GetService()->RegisterGlobalCamera();
            _camera_controller.GetService()->SetAzimuth(0.0f);
            _camera_controller.GetService()->SetAltitude(-13.0f);
            _camera_controller.GetService()->SetDistance(10.0f);
        } // if


        auto menu = _ui_creator.Create(super::GetUICanvas(), super::GetResource());
        _title_menu_subject.AddObserver(menu);
        _title_menu_subject.Notify(true);


        if (auto game = _game.lock()) {
            auto option_system = game->GetOptionSystem();

            _option_system_subject.AddObserver(option_system);
            option_system->GetTitleMenuSubject()->AddObserver(menu);

            auto item0 = std::make_shared<ratchet::game::gamesystem::OptionSystemItem>([&]() {
                _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kDescriptionScene, ""));
                return true;
            });
            item0->SetText("操作説明");

            auto item1 = std::make_shared<ratchet::game::gamesystem::OptionSystemItem>([&]() {
                if (!_scene_end) {
                    _title_menu_subject.Notify(false);
                    _option_system_subject.Notify(false);
                    this->FadeOutStart();
                    _scene_end = true;
                } // if
                return true;
            });
            item1->SetText("ゲームスタート");


            auto item2 = std::make_shared<ratchet::game::gamesystem::OptionSystemItem>([&]() {
                ::PostQuitMessage(0);
                return true;
            });
            item2->SetText("終了");


            option_system->Initialize();
            option_system->AddItem(item1);
            option_system->AddItem(item0);
            option_system->AddItem(item2);
        } // if
        //this->Initialize();

        _bgm.Play();
    });

    return true;
}

bool ratchet::scene::TitleScene::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::scene::TitleScene::Release(void) {
    super::Release();
    if (auto game = _game.lock()) {
        game->GetOptionSystem()->Release();
        _option_system_subject.Clear();
        _title_menu_subject.Clear();
    } // if

    _bgm.Release();
    _stage.Release();
    return true;
}