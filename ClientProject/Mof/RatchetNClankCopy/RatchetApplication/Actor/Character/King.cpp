#include "King.h"

#include "../../Scene/GameScene.h"
#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"
#include "../../Component/HPComponent.h"
#include "../../Component/BillboardComponent.h"
#include "../../Factory/FactoryManager.h"
#include "../../Camera/FollowCameraController.h"
#include "../Character/Player.h"
#include "../../TutorialManager.h"
#include "../Gimmick/Fence.h"
#include "../../Scene/GameScene.h"


void ratchet::actor::character::King::PlayerActionLiberate(void) {
    auto type = static_cast<tutorial::TutorialManager::TutorialType>(_quest_index);
    tutorial::TutorialManager::GetInstance().Liberation(type);
}

void ratchet::actor::character::King::BarricadeCreate(ratchet::actor::Actor::Param* param, std::shared_ptr<ratchet::scene::Scene> out) {
    def::Transform transforms[]{
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -20.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -18.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -16.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -16.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -14.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -12.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -10.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -8.0f),Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-14.0f, -5.2f, -6.0f),Mof::CVector3(0.0f, 0.0f,0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-16.0f, -5.2f, -6.0f),Mof::CVector3(0.0f, 0.0f,0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-18.0f, -5.2f, -6.0f),Mof::CVector3(0.0f, 0.0f,0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-20.0f, -5.2f, -6.0f),Mof::CVector3(0.0f, 0.0f,0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-22.0f, -5.2f, -6.0f),Mof::CVector3(0.0f, 0.0f,0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
        def::Transform(Mof::CVector3(-24.0f, -5.2f, -6.0f),Mof::CVector3(0.0f, 0.0f,0.0f),Mof::CVector3(0.5f,0.15f,0.5f)),
    };
    param->tag = "barricade";
    auto game_scene = std::dynamic_pointer_cast<ratchet::scene::GameScene>(out);
    for (auto& transform : transforms) {
        param->transform.position = transform.position;
        param->transform.rotate = transform.rotate;
        param->transform.scale = transform.scale;
        auto barricade = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::gimmick::Fence>("../Resource/builder/barricade.json", param);
        game_scene->AddElement(barricade);
        _created_barricade.push_back(barricade);
    } // for
    param->transform = def::Transform();
}

ratchet::actor::character::King::King() :
    super(),
    _actor_container(),
    _quest_index(0),
    _quest_count(2),
    _scarecrow_view_camera_controller(),
    _scarecrow_view_position(3.0f, -3.0f, 0.0f),
    _effect_container(),
    _free_talk_index(0),
    _event_icon_show(true),
    _created_barricade(),
    _scarecrow_generate_datas() {

    auto con = std::make_shared<ratchet::camera::FollowCameraController>();
    auto camera = std::make_shared<ratchet::camera::Camera>();
    camera->Initialize();
    con->SetCamera(camera);
    _scarecrow_view_camera_controller.SetService(con);
    {
        auto data_0 = ScarecrowGenerateData();
        data_0.position.push_back(Mof::CVector3(-12.0f, -5.0f, -4.0f));

        auto data_1 = ScarecrowGenerateData();
        data_1.position.push_back(Mof::CVector3(-17.0f, -5.0f, -15.0f));
        data_1.position.push_back(Mof::CVector3(-20.0f, -5.0f, -9.0f));

        _scarecrow_generate_datas.push_back(std::move(data_0));
        _scarecrow_generate_datas.push_back(std::move(data_1));
    }
}

ratchet::actor::character::King::~King() {
}

void ratchet::actor::character::King::OnNotify(const ratchet::actor::character::ScarecrowEndMessage& msg) {
    ut::EraseRemove(_created_scarecrows, msg.ptr);
    if (_created_scarecrows.empty()) {
        for (auto actor : _created_barricade) {
            actor->End();
        } // for
        _created_barricade.clear();

        auto message = ratchet::game::gamesystem::text::TextSystemMessage();
        auto type_temp = static_cast<int>(decltype(message.type)::TutorialEventNo0End) + _quest_index;
        message.type = static_cast<decltype(message.type)>(type_temp);
        message.on_close = [&]() {
            auto player_actor = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player> >("player");
            auto camera_controller = player_actor->GetComponent<component::CameraComponent>()->GetCameraController()->GetService();

            auto target = super::GetPosition();
//            auto player_camera = camera_controller;
            auto dir = target - player_actor->GetPosition();
            camera_controller->SetAzimuth(math::ToDegree(std::atan2(-dir.z, dir.x)));
            camera_controller->SetAltitude(20.0f);
            return true;
        };
        super::GetTextSystemMessageSubject()->Notify(message);

        this->_event_icon_show = true;
        _event_active = false;

        auto billboard = super::GetComponent<component::BillboardComponent>();
        billboard->Activate();
        _quest_index++;
    } // if
}

void ratchet::actor::character::King::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_question_texture = ptr;
}
void ratchet::actor::character::King::SetGameScene(const std::shared_ptr<scene::Scene>& ptr) {
    this->_actor_container = ptr;
}

void ratchet::actor::character::King::SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr) {
    this->_effect_container = ptr;
}

void ratchet::actor::character::King::SetHelpDesk(const std::shared_ptr<ratchet::game::gamesystem::HelpDesk>& ptr) {
    this->_help_desk = ptr;
}

bool ratchet::actor::character::King::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);
    return true;
}

bool ratchet::actor::character::King::Update(float delta_time) {
    super::Update(delta_time);
    auto camera = _scarecrow_view_camera_controller.GetService();
    auto info = camera::CameraController::CameraInfo();
    info.ideal_position = super::GetPosition();
    camera->Update(delta_time, info);
    return true;
}

bool ratchet::actor::character::King::Render(void) {
    super::Render();
    return true;
}

void ratchet::actor::character::King::Talk(void) {
    auto param = ratchet::actor::Actor::Param();
    //auto out = _actor_container.lock();
    auto effect = _effect_container.lock();
    //auto player = _player.lock();
    auto player = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetTalkedTarget());


    auto billboard = super::GetComponent<component::BillboardComponent>();
    auto dir = Mof::CVector3(super::GetPosition() - player->GetPosition());
    float angle_y = std::atan2f(-dir.z, dir.x) + math::kHalfPi;
    super::SetRotate(Mof::CVector3(0.0f, angle_y, 0.0f));
    billboard->SetOffsetRotation(-super::GetRotate());

    if (_quest_index < _quest_count) {
        auto message = ratchet::game::gamesystem::text::TextSystemMessage();
        auto type_temp = static_cast<int>(decltype(message.type)::TutorialEventNo0) + _quest_index;
        message.type = static_cast<decltype(message.type)>(type_temp);
        message.on_close = [&]() {
            auto player_actor = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player> >("player");
            auto camera_controller = player_actor->GetComponent<component::CameraComponent>()->GetCameraController()->GetService();

            _event_icon_show = false;
            camera_controller->RegisterGlobalCamera();

            auto target = Mof::CVector3(-12.0f, -5.0f, -4.0f);
//            auto player_camera = _player_view_camera_controller->GetService();
            auto dir = target - player_actor->GetPosition();
            camera_controller->SetAzimuth(math::ToDegree(std::atan2(-dir.z, dir.x)));

            auto billboard = super::GetComponent<component::BillboardComponent>();
            billboard->Inactivate();
            return true;
        };
        super::GetTextSystemMessageSubject()->Notify(message);
        auto game_scene = std::dynamic_pointer_cast<ratchet::scene::GameScene>(_actor_container.lock());

        if (!_event_active) {
            if (message.type == decltype(message.type)::TutorialEventNo1) {
                this->BarricadeCreate(&param, game_scene);
            } // if

            auto& scarecrow_transforms = _scarecrow_generate_datas.at(_quest_index);
            // create
            param.tag = "Scarecrow";
            for (auto& position : scarecrow_transforms.position) {
                param.transform.position = position;
                auto scarecrow = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::character::Scarecrow>("../Resource/builder/scarecrow.json", &param);
                auto emitter = effect->CreateEmitter(effect::EffectType::BasicDamage);
                auto star_emitter = effect->CreateEmitter(effect::EffectType::PopStar);
                scarecrow->SetEffectEmitter(emitter);
                scarecrow->SetStarEffectEmitter(star_emitter);
                scarecrow->GetScarecrowEndMessageSubject()->AddObserver(std::dynamic_pointer_cast<ratchet::actor::character::King>(shared_from_this()));
                scarecrow->GetCharacterDamageApplyMessageSubject()->AddObserver(game_scene);
                game_scene->AddElement(scarecrow);
                _created_scarecrows.push_back(scarecrow);
            } // for

            auto player_actor = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player> >("player");
            auto camera_camera_controller = player_actor->GetComponent<component::CameraComponent>()->GetCameraController()->GetService();
            //auto player_camera = _player_view_camera_controller->GetService();
            auto dir = super::GetPosition() - player->GetPosition();
            camera_camera_controller->SetAzimuth(math::ToDegree(std::atan2(-dir.z, dir.x)));
            this->PlayerActionLiberate();
  //          ut::SafeDelete(&param);
        //    _quest_index++;
        } // if
        _event_active = true;
    } // if
    else {
        auto message = ratchet::game::gamesystem::text::TextSystemMessage();
        if (_free_talk_index == 0) {
            message.type = decltype(message.type)::KingTextEvent;

            message.on_close = [&]() {
                tutorial::TutorialManager::GetInstance().Complete();

                auto billboard = super::GetComponent<component::BillboardComponent>();
                billboard->Inactivate();

                if (event::EventReferenceTable::Singleton().Exist("GameManager")) {
                    auto game = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::game::GameManager>>("GameManager");
                    auto help_desk = game->GetHelpDesk();
                    help_desk->RegisterQuest(ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::EnemyDestroy));
                } // if

                auto player_actor = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player> >("player");
                auto camera_controller = player_actor->GetComponent<component::CameraComponent>()->GetCameraController()->GetService();

                camera_controller->SetAzimuth(10);
                camera_controller->SetAltitude(20);

                if (auto help_desk = _help_desk.lock()) {
                    help_desk->Show();
                } // if
                auto hp_com = player_actor->GetComponent<component::HpComponent>();
                if (hp_com) {
                    hp_com->RegisterUI();
                } // if
                return true;
            };
            _free_talk_index++;
        } // if
        else {
            message.type = decltype(message.type)::KingFreeTalkTextEvent;
        } // else
        super::GetTextSystemMessageSubject()->Notify(message);
    } // else
}