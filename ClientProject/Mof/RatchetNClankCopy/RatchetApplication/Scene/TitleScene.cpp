#include "TitleScene.h"
#include "../Gamepad.h"
#include "Base/Resource/ResourceFont.h"
#include "../Game/Audio/AudioUtility.h"
#include "TitleSceneInitializer.h"
#include "DescriptionScene.h"


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

void ratchet::scene::TitleScene::InitializeOption(void) {
    auto menu = _ui_creator.Create(super::GetUICanvas(), super::GetResource());
    _title_menu_subject.AddObserver(menu);
    _title_menu_subject.Notify(true);

    if (auto game = _game.lock()) {

        auto option_system = game->GetOptionSystem();
        auto se_player = super::GetSEPlayer();
        option_system->SetSEPlayer(se_player);

        _option_system_subject.AddObserver(option_system);
        option_system->GetTitleMenuSubject()->AddObserver(menu);

        auto item0 = std::make_shared<ratchet::game::gamesystem::OptionSystemItem>([&]() {
            _how_to_play.Show();
            return true;
        });
        item0->SetText("操作説明");

        auto item1 = std::make_shared<ratchet::game::gamesystem::OptionSystemItem>([&]() {
            if (!_how_to_play.IsShow()) {
                if (!_scene_end) {
                    _title_menu_subject.Notify(false);
                    _option_system_subject.Notify(false);
                    this->FadeOutStart();
                    _scene_end = true;
                } // if
            } // if
            return true;
        });
        item1->SetText("ゲームスタート");


        auto item2 = std::make_shared<ratchet::game::gamesystem::OptionSystemItem>([&]() {
            if (!_how_to_play.IsShow()) {

                _option_system_subject.Notify(false);
                _scene_end = true;
                ::PostQuitMessage(0);
            } // if
            return true;
        });
        item2->SetText("終了");


        option_system->Initialize();
        option_system->AddItem(item1);
        option_system->AddItem(item0);
        option_system->AddItem(item2);
    } // if

}

bool ratchet::scene::TitleScene::SceneUpdate(float delta_time) {
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        if (_how_to_play.IsShow()) {
            _how_to_play.Hide();


            if (auto game = _game.lock()) {
                auto option_system = game->GetOptionSystem();
                option_system->Clear();
                this->InitializeOption();
                option_system->OnNotify(true);
                //option_system->OnNotify(true);
            } // if

        } // if
        else {
            ::PostQuitMessage(0);
        } // else
        return false;
    } // if

    // 一定時間入力を受け付けない
    if (_input_flag) {
        if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
            ::g_pInput->IsKeyPush(MOFKEY_SPACE) || ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
            if (!_scene_end) {
                _option_system_subject.Notify(true);
            } // if
        } // if
    } // if
    if (_input_timer.Tick(delta_time)) {
        _input_flag = true;
    } // if


    // フェード
    bool effect_end = super::SceneUpdate(delta_time);
    if (effect_end && _transition_state == TransitionState::End) {
        _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kGameScene, ""));
    } // if

    // title
    _demo_actor->Update(delta_time);
    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    auto pos = Mof::CVector3(10.0f, -2.0f, -15.0f);
    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(_camera_controller.GetService()->GetAzimuth()) + 0.2f);
    camera_info.target_position = pos;
    _camera_controller.GetService()->Update(delta_time, camera_info);
    _logo.Update(delta_time);


    // sound
    auto bgm_player = super::GetBGMPlayer();
    auto se_player = super::GetSEPlayer();
    if (_scene_end) {
        super::GetBGMPlayer()->Recieve(ratchet::game::audio::BGMEvent(
            game::audio::BGMType::Title, game::audio::BGMEventCommand::SetVolume(bgm_player->GetVolume(game::audio::BGMType::Title) * 0.9f)
        ));
    } // if
    bgm_player->Update();
    se_player->Update();
    return true;
}

bool ratchet::scene::TitleScene::LoadingUpdate(float delta_time) {
    _load_animation.Update(delta_time);
    return true;
}

bool ratchet::scene::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);

    _demo_actor->Render();
    _stage.Render();
    ::g_pGraphics->SetDepthEnable(false);

    _logo.Render();


    if (_how_to_play.IsShow()) {
        _how_to_play.Render(super::GetResource());
    } // if
    return true;
}

bool ratchet::scene::TitleScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    _load_animation.Render();
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
    _input_flag(false),
    _input_timer(),
    _show_how_to_play(false) {
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
    // shader
    auto effect = SceneEffect();
    effect.Load("../Resource/shader/fadein.hlsl");
    effect.CreateShaderBuffer("cbSceneEffectParam", sizeof(ratchet::cbSceneEffectParam));

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

            ::CoUninitialize();
            super::LoadComplete();

            this->Initialize();
        } // if
    });
    return true;
}

bool ratchet::scene::TitleScene::Initialize(void) {
    if (!super::IsLoaded()) {
        return false;
    } // if
    super::Initialize();

    auto initializer = TitleSceneInitializer();
    auto shared_this = std::dynamic_pointer_cast<TitleScene>(shared_from_this());;
    initializer.Execute(shared_this);

    this->InitializeOption();

    return true;
}

bool ratchet::scene::TitleScene::Release(void) {
    super::Release();
    if (auto game = _game.lock()) {
        game->GetOptionSystem()->Release();
        _option_system_subject.Clear();
        _title_menu_subject.Clear();
    } // if

    _stage.Release();
    return true;
}