#include "EnemyViewEvent.h"

#include "../Factory/FactoryManager.h"
#include "../Actor/Character/Queen.h"
#include "../Event/EventReferenceTable.h"


void ratchet::event::EnemyViewEvent::GenerateQueen(void) {
    auto param = new ratchet::actor::Actor::Param();
    //auto game_scene = event::EventReferenceTable::Singleton().Get<std::shared_ptr<scene::GameScene> >("GameScene");
    def::Transform npc_transforms[]{
        //def::Transform(Mof::CVector3(182.0f, -30.0f, 33.0f), Mof::CVector3(0.0f, 45.0f , 0.0f)),
        def::Transform(Mof::CVector3(182.0f, -29.5f, 33.0f), Mof::CVector3(0.0f, 45.0f , 0.0f)),
        //def::Transform(Mof::CVector3(5.0f, -5.0f, -5.0f), Mof::CVector3(0.0f, 0.0f , 0.0f)),
    };
    param->tag = "queen";
    param->name = "queen";
    for (auto& transform : npc_transforms) {
        param->transform.position = transform.position;
        param->transform.rotate = transform.rotate;
        param->transform.scale = transform.scale;
        auto queen = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::character::Queen>("../Resource/builder/queen.json", param);
        _game_scene.lock()->AddElement(queen);


        if (auto text = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::game::gamesystem::text::TextSystem> >("TextSystem")) {
            queen->GetTextSystemMessageSubject()->AddObserver(text);
        } // if
    } // for
    ut::SafeDelete(param);

}

ratchet::event::EnemyViewEvent::EnemyViewEvent() :
    super(),
    _camera(std::make_shared<ratchet::camera::Camera>()),
    _camera_controller(std::make_shared<ratchet::camera::AutoCameraController>()),
    _player_camera_controller(),
    _text_system_message_subject(),
    _text_system() {
    _camera->Initialize();
    _camera->Update();
    _camera_controller->SetCamera(_camera);
}

ratchet::event::EnemyViewEvent::~EnemyViewEvent() {
}

ratchet::event::EnemyViewEvent::CameraObservable* ratchet::event::EnemyViewEvent::GetCameraObservable(void) {
    return &this->_camera_subject;
}

void ratchet::event::EnemyViewEvent::SetStartPosition(Mof::CVector3 pos) {
    this->_start_position = pos;
}

void ratchet::event::EnemyViewEvent::SetPlayerCamera(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr) {
    this->_player_camera_controller = ptr;
}

bool ratchet::event::EnemyViewEvent::Initialize(void) {
    auto p = _player_camera_controller->GetService()->GetCameraPosition();
    auto player_camera = _player_camera_controller->GetService();
    Mof::CVector3 target = Mof::CVector3(65.0, -30.0f, 82.0f);
    Mof::CVector3 dir = target - p;
    dir.y = 0.0f;
    dir.Normal(dir);

    std::vector<Mof::CVector3> control_points_target = {
        target + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        //target + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        //target + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        target + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        //target + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        target + Mof::CVector3(190.0f, -30.0f, -70.0f) ,
        target + Mof::CVector3(190.0f, 20.0f, -70.0f) ,
    };
    std::vector<Mof::CVector3> control_points_position = {
        p ,
        p + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        p + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        p + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        p + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        p + Mof::CVector3(0.0f, 20.0f, 60.0f) * dir + Mof::CVector3(0.0f, 10.0f, 0.0f),
        p + Mof::CVector3(0.0f, 20.0f, 60.0f) * dir + Mof::CVector3(0.0f, 10.0f, 0.0f),
    };

    _camera_controller->TimerReset(6.0f);
    _camera_controller->RegisterCameraPositionControllPoint(control_points_position);
    _camera_controller->RegisterCameraTargetControllPoint(control_points_target);
    _camera_controller->RegisterGlobalCamera();
    _camera->SetPosition(p);
    _camera->SetTarget(target);
    _camera->Update();

    this->GenerateQueen();



    if (event::EventReferenceTable::Singleton().Exist("GameManager")) {
        auto game = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::game::GameManager>>("GameManager");
        auto help_desk = game->GetHelpDesk();
        help_desk->RegisterQuest(ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::ToFront));
    } // if
    return true;
}

bool ratchet::event::EnemyViewEvent::Update(float delta_time) {
    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _camera_controller->Update(delta_time, camera_info);

    if (_camera_controller->IsCompleted()) {
        {
            auto message = ratchet::game::gamesystem::text::TextSystemMessage();
            message.type = decltype(message.type)::TeachPlazaEvent;
            _text_system_message_subject.Notify(message);
        }

        auto message = EnemyViewEventEndMessage();
        message.end = true;
        _enemy_view_event_message_subject.Notify(message);

        auto info = ratchet::camera::CameraController::CameraInfo();
        info.start_position = _camera_controller->GetCameraPosition();
        info.target_position = math::vec3::kZero;
        _camera_subject.Notify(info);

        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}