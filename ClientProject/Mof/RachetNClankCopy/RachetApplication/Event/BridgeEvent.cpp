#include "BridgeEvent.h"


rachet::BridgeEvent::BridgeEvent() :
    super(),
    _for_bridge_event_actors(),
    _stage(),
    _bridge_view_camera(),
    _bridge_view_camera_controller(),
    _ideal_position() {
    _ideal_position = Mof::CVector3(60.0f, 0.0f, 0.0f);
    _bridge_view_camera_controller.SetSpring(15.0f);
    _bridge_view_camera_controller.SetDumping(10.0f);
}

rachet::BridgeEvent::~BridgeEvent() {
}

void rachet::BridgeEvent::OnNotify(const char* type, const std::shared_ptr<rachet::Actor>& ptr) {
    if (type == "EnemyDead") {
        if (ptr) {
            ptr->RemoveObserver(std::dynamic_pointer_cast<rachet::BridgeEvent>(shared_from_this()));
            ut::SwapPopback(_for_bridge_event_actors, ptr);
        } // if

        if (_for_bridge_event_actors.empty()) {
            auto quest = rachet::GameQuest(rachet::GameQuest::Type::GoHome);
            _quest_subject.Notify(quest);


            // view
            _bridge_view_camera_controller.RegisterGlobalCamera();
            auto info = rachet::CameraController::CameraInfo();
            auto globel = Mof::CGraphicsUtilities::GetCamera();
            info.start_position = globel->GetViewPosition();
            info.camera_front = globel->GetViewFront();

            for (auto gimmick : _stage->GetGimmickArray()) {
                if (gimmick->GetType() == StageObjectType::Bridge) {
                    info.target_position = gimmick->GetPosition();
                    info.ideal_position = _ideal_position;
                    
                    {
                        auto send_info = rachet::CameraController::CameraInfo();
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

void rachet::BridgeEvent::SetStage(Stage* ptr) {
    this->_stage = ptr;
}

base::core::Observable<const rachet::CameraController::CameraInfo&>* rachet::BridgeEvent::GetCameraSubject(void) {
    return &this->_camera_subject;
}

base::core::Observable<const rachet::GameQuest&>* rachet::BridgeEvent::GetQuestSubject(void) {
    return &this->_quest_subject;
}

bool rachet::BridgeEvent::EventActorsEmpty(void) const {
    return _for_bridge_event_actors.empty();
}

bool rachet::BridgeEvent::Initialize(void) {
    _for_bridge_event_actors.clear();

    _bridge_view_camera = std::make_shared<rachet::Camera>();
    _bridge_view_camera->Initialize();
    _bridge_view_camera->Update();
    _bridge_view_camera_controller.SetCamera(_bridge_view_camera);
    return true;
}

bool rachet::BridgeEvent::Update(float delta_time) {
    auto camera_info = rachet::CameraController::CameraInfo();
    camera_info.ideal_position = _ideal_position;
    _bridge_view_camera_controller.Update(delta_time, camera_info);

#ifdef _DEBUG
#endif // _DEBUG
    if (::g_pInput->IsKeyPush(MOFKEY_B)) {
        this->AllDelete();
    } // if
    return true;
}

void rachet::BridgeEvent::AddTriggerActor(const std::shared_ptr<rachet::Actor>& ptr) {
    _for_bridge_event_actors.push_back(ptr);
    ptr->AddObserver(std::dynamic_pointer_cast<rachet::BridgeEvent>(shared_from_this()));
}

void rachet::BridgeEvent::AllDelete(void) {
    _for_bridge_event_actors.clear();
    this->OnNotify("EnemyDead", nullptr);
    for (auto actor : _for_bridge_event_actors) {
        actor->End();
    } // for
}