#include "GameScene.h"

#include "../Gamepad.h"
#include "../Event/TextSystemStartEvent.h"
#include "../Event/HitStopEvent.h"

#include "../Event/EventReferenceTable.h"
#include "GameSceneInitializer.h"
#include "../TutorialManager.h"
#include "../Game/Audio/SEPlayer.h"
#include "../MessageObservation.h"


void ratchet::scene::GameScene::AddElement(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    // add
    ptr->AddObserver(shared_from_this());
    _game_world.AddActor(ptr);
    _renderer.AddElement(ptr);
    _physic_world.AddActor(ptr);
}

void ratchet::scene::GameScene::RemoveElement(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    // remove
    _game_world.RemoveActor(ptr);
    _renderer.RemoveElement(ptr);
    _physic_world.RemoveActor(ptr);
}

void ratchet::scene::GameScene::ReInitialize(void) {
    _renderer.Reset();
    _game_world.Reset();
    _physic_world.Reset();
    this->Initialize();
}

bool ratchet::scene::GameScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);

    {
        tutorial::TutorialManager::GetInstance().Complete();
        tutorial::TutorialManager::GetInstance().Liberation(tutorial::TutorialManager::TutorialType::Attack);
        tutorial::TutorialManager::GetInstance().Liberation(tutorial::TutorialManager::TutorialType::Weapon);
    }

    for (auto& ptr : _created_actors) {
        this->AddElement(ptr);
    } // for
    _created_actors.clear();
    for (auto& ptr : _delete_actors) {
        this->RemoveElement(ptr);
    } // for
    _delete_actors.clear();


    if (_player_dead) {
        auto init = GameSceneInitializer();
        init.AddPlayer(_game.lock(), _event.lock(), std::dynamic_pointer_cast<GameScene>(shared_from_this()));
        _player_dead = false;
//        this->ReInitialize();
    } // if


    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
        if (_how_to_play.IsShow()) {
            _how_to_play.Hide();
            super::SetState(State::Active);
        } // if
    } // if


    if (_state != super::State::Pause) {
        // input
        if (_state != super::State::Sleep) {
            _game_world.Input();
        } // if

        // update
        _stage.Update(delta_time);
        _game_world.Update(delta_time);
    } // if
    // collision
    _physic_world.CollisionStage(&_stage);
    _physic_world.Update();


    if (_text_system->IsActive()) {
        if (!_text_system->Update()) {
            super::SetState(State::Active);
        } // if
    } // if
    _effect->Update(delta_time);

    auto bgm_player = super::GetBGMPlayer();
    auto se_player = super::GetSEPlayer();
    bgm_player->Update();
    se_player->Update();
    return true;
}

bool ratchet::scene::GameScene::LoadingUpdate(float delta_time) {
    _loading_dot_animation.Update(delta_time);
    return true;
}

bool ratchet::scene::GameScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);

    _stage.Render();
    super::GetLightManager()->Render();

    _renderer.Render();
    _effect->Render();

    ::g_pGraphics->SetDepthEnable(false);

    if (_text_system->IsActive()) {
        _text_system->Render();
    } // if


    if (_how_to_play.IsShow()) {
        _how_to_play.Render(super::GetResource());
    } // if

    return true;
}

bool ratchet::scene::GameScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    _loading_dot_animation.Render();
    return true;
}

ratchet::scene::GameScene::GameScene() :
    _created_actors(),
    _delete_actors(),
    _game_world(),
    _renderer(),
    _physic_world(),
    _stage(),
    _re_initialize(false),
    _game(),
    _event(),
    _text_system(std::make_shared<ratchet::game::gamesystem::text::TextSystem>()),
    _loading_counter(),
    _loading_dot_count(0),
    _how_to_play() {
    _loading_counter.Initialize(1.0f, true);
}

ratchet::scene::GameScene::~GameScene() {
}

void ratchet::scene::GameScene::OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    if (type == "AddRequest") {
        ptr->AddObserver(shared_from_this());
        _created_actors.push_back(ptr);
    } // if
    if (type == "DeleteRequest") {
        auto tag = ptr->GetTag();
        if (tag == "Enemy" ||
            tag == "Scarecrow") {
            auto se = ratchet::game::audio::SEEvent();
            se.type = decltype(se.type)::EnemyDead;
            se.command = decltype(se.command)::Play();
            super::GetSEPlayer()->Recieve(se);
        } // if
        else if (tag == "EnemyBullet") {
            auto info = effect::Effect::Info();
            info.init_param.type = effect::EffectType::EnemyBulletEnd;
            info.init_param.life_duration = 1.0f;
            info.init_param.color = def::color_rgba::kWhite;
            info.init_param.transform.position = ptr->GetPosition();

            info.update_param.color = Mof::CVector4(0.0f, 0.0f, 0.0f, -0.05f);
            info.update_param.scale = Mof::CVector3(0.05f, 0.0f, 0.05f);
            _enemy_bullet_end_effect_emitter->Emit(info);
        } // else if



        ptr->RemoveObserver(shared_from_this());
        _delete_actors.push_back(ptr);
    } // if
    if (type == "PlayerDead") {
        // retry
        _player_dead = true;
        _re_initialize = true;

        ptr->RemoveObserver(shared_from_this());
        _delete_actors.push_back(ptr);

    } // if
    if (type == "GameClear") {
        _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kClearScene, ""));
    } // if
}

void ratchet::scene::GameScene::OnNotify(const ratchet::game::gamesystem::ShopSystem::Info& info) {
    if (info.close) {
        this->_state = super::State::Active;
    } // if
    else {
        this->_state = super::State::Pause;
    } // else
}

void ratchet::scene::GameScene::OnNotify(const ratchet::event::StageViewEventMessage& message) {
    if (message.end) {
        if (auto event = _event.lock()) {
            auto text_system_start_event = event->CreateGameEvent<ratchet::event::TextSystemStartEvent>();
            text_system_start_event->SetTextSystem(_text_system);
            text_system_start_event->SetGameScene(shared_from_this());
        } // if
    } // if
}

void ratchet::scene::GameScene::OnNotify(const ratchet::event::ShipEventEndMessage& message) {
    auto bgm_player = super::GetBGMPlayer();

    using namespace game::audio;
    {
        auto e = BGMEvent(BGMType::Battle, BGMEventCommand::Stop());
        super::GetBGMPlayer()->Recieve(e);
    }
    {
        auto e = ratchet::game::audio::BGMEvent(BGMType::Field, BGMEventCommand::Play());
        super::GetBGMPlayer()->Recieve(e);
    }
}

void ratchet::scene::GameScene::OnNotify(const ratchet::actor::character::CharacterDamageApplyMessage& message) {
//    OutputDebugString("GameScene \n");
    if (auto e = _event.lock()) {
        auto event = e->CreateGameEvent<event::HitStopEvent>();
        event->SetGameScene(std::dynamic_pointer_cast<scene::GameScene>(shared_from_this()));
        event->Initialize();

        auto se = ratchet::game::audio::SEEvent();
        se.type = decltype(se.type)::EnemyDamage;
        se.command = decltype(se.command)::Play();
        super::GetSEPlayer()->Recieve(se);
    } // if
}

void ratchet::scene::GameScene::OnNotify(const ContactEnemyMessage& message) {
    auto bgm_player = super::GetBGMPlayer();
    using namespace game::audio;
    {
        auto e = ratchet::game::audio::BGMEvent();
        e.type = decltype(e.type)::Battle;
        e.command = decltype(e.command)::Play();
        super::GetBGMPlayer()->Recieve(e);
    }
    {
        auto e = ratchet::game::audio::BGMEvent();
        e.type = decltype(e.type)::Field;
        e.command = decltype(e.command)::Stop();
        super::GetBGMPlayer()->Recieve(e);
    }
}

void ratchet::scene::GameScene::OnNotify(game::gamesystem::text::TextSystemOpenMessageListener::Message message) {
    super::SetState(State::Sleep);
}

void ratchet::scene::GameScene::OnNotify(game::gamesystem::text::TextSystemClosedMessageListener::Message message) {
    super::SetState(State::Active);
}

void ratchet::scene::GameScene::SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr) {
    this->_game = ptr;
}

void ratchet::scene::GameScene::SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr) {
    this->_event = ptr;
}

std::string ratchet::scene::GameScene::GetName(void) {
    return ratchet::scene::SceneType::kGameScene;
}

bool ratchet::scene::GameScene::Load(std::shared_ptr<ratchet::scene::Scene::Param> param) {
    super::Load(param);

    game::gamesystem::text::TextSystemOpenMessageObservation::Singleton().LinkObservation(
        std::dynamic_pointer_cast <ratchet::game::gamesystem::text::TextSystemOpenMessageListener
        >(shared_from_this())
    );

    super::_load_thread = std::thread([&]() {
        if (auto r = _resource.lock()) {
            auto path = "../Resource/scene_resource/game_scene.txt";
            r->Load(path);

            auto bgm_player = super::GetBGMPlayer();
            {
                auto bgm = r->Get<std::shared_ptr<Mof::CStreamingSoundBuffer>>("../Resource/bgm/battle.mp3");
                bgm_player->AddSound(ratchet::game::audio::BGMType::Battle, bgm);
            }
            {
                auto bgm = r->Get<std::shared_ptr<Mof::CStreamingSoundBuffer>>("../Resource/bgm/field.mp3");
                bgm_player->AddSound(ratchet::game::audio::BGMType::Field, bgm);
            }
        } // if
        if (!_stage.Load("../Resource/stage/stage.json")) {
            //return false;
        } // if

        if (auto game = _game.lock()) {
            game->GameSystemLoad();
        } // if

        super::LoadComplete();
        _text_system->Load();

        this->Initialize();

        // effect
        _enemy_bullet_end_effect_emitter = _effect->CreateEmitter(effect::EffectType::EnemyBulletEnd);

        auto bgm_player = super::GetBGMPlayer();
        {
            auto e = ratchet::game::audio::BGMEvent();
            e.type = decltype(e.type)::Field;
            e.command = decltype(e.command)::Play();
            super::GetBGMPlayer()->Recieve(e);
        }
    });
    return true;
}

bool ratchet::scene::GameScene::Initialize(void) {
    if (!super::IsLoaded()) {
        return false;
    } // if

    auto initializer = GameSceneInitializer();
    auto shared_this = std::dynamic_pointer_cast<GameScene>(shared_from_this());;

    auto game = _game.lock();
    auto event = _event.lock();
    _effect = std::make_shared<ratchet::effect::EffectContainer>();
    _effect->SetResourceManager(super::GetResource());
    initializer.Execute(game, event, shared_this);

    {
        auto item0 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            this->_subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kTitleScene, ""));
            return true;
        });
        item0->SetText("É^ÉCÉgÉãÇ…ñﬂÇÈ");

        auto item1 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            this->SetState(State::Pause);
            _how_to_play.Show();
//            _show_how_to_play = true;
            return true;
        });
        item1->SetText("ëÄçÏê‡ñæ");

        auto item2 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            _game.lock()->GetGamePauseSystem()->Inactive();
            super::SetState(scene::Scene::State::Active);
            return true;
        });
        item2->SetText("Ç‡Ç«ÇÈ");


        game->GetGamePauseSystem()->AddItem(item2);
        game->GetGamePauseSystem()->AddItem(item1);
        game->GetGamePauseSystem()->AddItem(item0);
        game->GetGamePauseSystem()->SetSEPlayer(super::GetSEPlayer());
    }
    _re_initialize = false;
    return true;
}

bool ratchet::scene::GameScene::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_BACK)) {
        if (auto game = _game.lock()) {
            if (!game->GetGamePauseSystem()->IsActive()) {
                if (!_event.lock()->GetEvent<ratchet::event::StageViewEvent>()) {
                    if (this->_state != super::State::Pause) {
                        this->_state = super::State::Pause;
                        _pause_menu_subject.Notify(true);
                    } // if
                } // if
            } // if
        } // if
    } // if
    return true;
}

bool ratchet::scene::GameScene::Release(void) {
    ratchet::event::EventReferenceTable::Singleton().Dispose("GameManager");
    ratchet::event::EventReferenceTable::Singleton().Reset();

    using o = ratchet::ObservationManager();

    super::Release();
    _stage.Release();
    if (auto game = _game.lock()) {
        game->GetUserActionHelper()->DisposeUI();
        game->GetGamePauseSystem()->Clear();
        _pause_menu_subject.Clear();
        game->GameSystemRelease();
    } // if

    if (_text_system) {
        _text_system->Release();
    } // if
    _text_system.reset();
    return true;
}