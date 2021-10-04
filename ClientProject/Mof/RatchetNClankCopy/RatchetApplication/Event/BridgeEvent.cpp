#include "BridgeEvent.h"

#include "EventReferenceTable.h"
#include "../Game/GameManager.h"
#include "../Scene/GameScene.h"
#include "ShipEvent.h"
#include "../Stage/Gimmick/Bridge.h"
#include "../Game/GameSystem/GameQuest.h"


ratchet::event::BridgeEvent::BridgeEvent() :
    super(),
    _for_bridge_event_actors(),
    _stage(),
    _bridge_view_camera(std::make_shared<ratchet::camera::Camera>()),
    _bridge_view_camera_controller(),
    _ideal_position(),
    _enable(false),
    _time(3.0f),
    _timer() {
    _bridge_view_camera->Initialize();
    _bridge_view_camera->Update();
    _bridge_view_camera_controller.SetCamera(_bridge_view_camera);


    if (event::EventReferenceTable::Singleton().Exist("Stage")) {
        _stage = event::EventReferenceTable::Singleton().Get<Stage*>("Stage");
    } // if
}

ratchet::event::BridgeEvent::~BridgeEvent() {
}

void ratchet::event::BridgeEvent::OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) {
}

void ratchet::event::BridgeEvent::SetStage(Stage* ptr) {
    this->_stage = ptr;
}

base::core::Observable<const ratchet::camera::CameraController::CameraInfo&>* ratchet::event::BridgeEvent::GetCameraSubject(void) {
    return &this->_camera_subject;
}

base::core::Observable<const ratchet::game::gamesystem::GameQuest&>* ratchet::event::BridgeEvent::GetQuestSubject(void) {
    return &this->_quest_subject;
}

bool ratchet::event::BridgeEvent::EventActorsEmpty(void) const {
    return _for_bridge_event_actors.empty();
}

bool ratchet::event::BridgeEvent::Initialize(void) {
    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _bridge_view_camera_controller.RegisterGlobalCamera();
    _bridge_view_camera_controller.SetInfo(camera_info);
    _ideal_position = Mof::CVector3(22.0f, 3.0f, -12.0f);
    auto target_position = Mof::CVector3(130.0f, -40.0f, 10.0f);

    std::vector<Mof::CVector3 > positions = {
        //Mof::CVector3(-5.0f, 0.0f, 5.0f),
        _ideal_position,
        _ideal_position,
    };
    std::vector<Mof::CVector3 > targets = {
        target_position,
        target_position
    };
    _timer.Initialize(_time, false);
    _bridge_view_camera_controller.TimerReset(_time);
    _bridge_view_camera_controller.RegisterCameraPositionControllPoint(positions);
    _bridge_view_camera_controller.RegisterCameraTargetControllPoint(targets);
    _bridge_view_camera_controller.RegisterGlobalCamera();

    _bridge_view_camera->SetPosition(_ideal_position);
    _bridge_view_camera->SetTarget(target_position);
    _bridge_view_camera->Update();

    for (auto gimmick : _stage->GetGimmickArray()) {
        if (gimmick->GetType() == StageObjectType::Bridge) {
            gimmick->ActionStart();
        } // for
    } // if
    _enable = true;

    if (event::EventReferenceTable::Singleton().Exist("GameManager")) {
        auto game = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::game::GameManager>>("GameManager");
        auto help_desk = game->GetHelpDesk();
        help_desk->RegisterQuest(ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::GoHome));
    } // if
    return true;
}

bool ratchet::event::BridgeEvent::Update(float delta_time) {
    if (_enable) {
        auto camera_info = ratchet::camera::CameraController::CameraInfo();
        _bridge_view_camera_controller.Update(delta_time, camera_info);
    } // if

    if (_timer.Tick(delta_time)) {
        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}