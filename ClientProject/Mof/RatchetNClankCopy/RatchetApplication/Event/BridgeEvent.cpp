#include "BridgeEvent.h"


ratchet::event::BridgeEvent::BridgeEvent() :
    super(),
    _for_bridge_event_actors(),
    _stage(),
    _bridge_view_camera(),
    _bridge_view_camera_controller(),
    _ideal_position(),
    _enable(false) {
    _ideal_position = Mof::CVector3(60.0f, 0.0f, 0.0f);
    _bridge_view_camera_controller.SetSpring(15.0f);
    _bridge_view_camera_controller.SetDumping(10.0f);
}

ratchet::event::BridgeEvent::~BridgeEvent() {
}

void ratchet::event::BridgeEvent::OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    if (type == "EnemyDead") {
        _enable = true;

        if (ptr) {
            ptr->RemoveObserver(std::dynamic_pointer_cast<ratchet::event::BridgeEvent>(shared_from_this()));
            ut::SwapPopback(_for_bridge_event_actors, ptr);
        } // if

        if (_for_bridge_event_actors.empty()) {
            auto quest = ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::GoHome);
            _quest_subject.Notify(quest);


            // view
            _bridge_view_camera_controller.RegisterGlobalCamera();
            auto info = ratchet::camera::CameraController::CameraInfo();
            auto globel = Mof::CGraphicsUtilities::GetCamera();
            info.start_position = globel->GetViewPosition();
            info.camera_front = globel->GetViewFront();

            for (auto gimmick : _stage->GetGimmickArray()) {
                if (gimmick->GetType() == StageObjectType::Bridge) {
                    info.target_position = gimmick->GetPosition();
                    info.ideal_position = _ideal_position;

                    {
                        auto send_info = ratchet::camera::CameraController::CameraInfo();
                        send_info.start_position = _ideal_position;
                        _camera_subject.Notify(send_info);
                    }
                    gimmick->ActionStart();
                } // if
            } // for

            _bridge_view_camera_controller.SetInfo(info);
        } // if
    } // if
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
    _enable = false;
    _for_bridge_event_actors.clear();

    _bridge_view_camera = std::make_shared<ratchet::camera::Camera>();
    _bridge_view_camera->Initialize();
    _bridge_view_camera->Update();
    _bridge_view_camera_controller.SetCamera(_bridge_view_camera);

    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _bridge_view_camera_controller.SetInfo(camera_info);
    return true;
}

bool ratchet::event::BridgeEvent::Update(float delta_time) {
#ifdef _DEBUG
    if (::g_pInput->IsKeyPush(MOFKEY_B)) {
        this->AllDelete();
    } // if
#endif // _DEBUG

    if (_enable) {
        auto camera_info = ratchet::camera::CameraController::CameraInfo();
        camera_info.ideal_position = _ideal_position;

        _bridge_view_camera_controller.Update(delta_time, camera_info);
    } // if
    return true;
}

void ratchet::event::BridgeEvent::AddTriggerActor(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    _for_bridge_event_actors.push_back(ptr);
    ptr->AddObserver(std::dynamic_pointer_cast<ratchet::event::BridgeEvent>(shared_from_this()));
}

void ratchet::event::BridgeEvent::AllDelete(void) {
    _for_bridge_event_actors.clear();
    this->OnNotify("EnemyDead", nullptr);
    for (auto actor : _for_bridge_event_actors) {
        actor->End();
    } // for
}