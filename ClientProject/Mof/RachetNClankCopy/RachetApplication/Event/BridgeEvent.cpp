#include "BridgeEvent.h"

my::BridgeEvent::BridgeEvent() :
    _for_bridge_event_actors(),
    _stage(),
    _bridge_view_camera(),
    _bridge_view_camera_controller(),
    _ideal_position() {
    _ideal_position = Mof::CVector3(60.0f, 0.0f, 0.0f);
    _bridge_view_camera_controller.SetSpring(15.0f);
    _bridge_view_camera_controller.SetDumping(10.0f);
}

my::BridgeEvent::~BridgeEvent() {
}

void my::BridgeEvent::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
    if (type == "EnemyDead") {
        if (ptr) {
            ptr->RemoveObserver(shared_from_this());
            ut::SwapPopback(_for_bridge_event_actors, ptr);
        } // if

        if (_for_bridge_event_actors.empty()) {
            //Observable::Notify();

            // view
            _bridge_view_camera_controller.RegisterGlobalCamera();
            auto info = my::CameraController::CameraInfo();
            auto globel = Mof::CGraphicsUtilities::GetCamera();
            info.start_position = globel->GetViewPosition();
            info.camera_front = globel->GetViewFront();

            for (auto gimmick : _stage->GetGimmickArray()) {
                if (gimmick->GetType() == StageObjectType::Bridge) {
                    info.target_position = gimmick->GetPosition();
                    info.ideal_position = _ideal_position;
                    
                    {
                        
                        auto send_info = my::CameraController::CameraInfo();
                        //send_info.camera_front = globel->GetViewFront();
                        send_info.start_position = _ideal_position;
                        Observable::Notify(send_info);
                    }
                    gimmick->ActionStart();
                } // if
            } // for

            _bridge_view_camera_controller.SetInfo(info);
        } // if
    } // if
}

void my::BridgeEvent::SetStage(Stage* ptr) {
    this->_stage = ptr;
}

bool my::BridgeEvent::EventActorsEmpty(void) const {
    return _for_bridge_event_actors.empty();
}

bool my::BridgeEvent::Initialize(void) {
    _for_bridge_event_actors.clear();

    _bridge_view_camera = std::make_shared<my::Camera>();
    _bridge_view_camera->Initialize();
    _bridge_view_camera->Update();
    _bridge_view_camera_controller.SetCamera(_bridge_view_camera);
    return true;
}

bool my::BridgeEvent::Update(float delta_time) {
    auto camera_info = my::CameraController::CameraInfo();
    camera_info.ideal_position = _ideal_position;
    _bridge_view_camera_controller.Update(delta_time, camera_info);
    return true;
}

void my::BridgeEvent::AddTriggerActor(const std::shared_ptr<my::Actor>& ptr) {
    _for_bridge_event_actors.push_back(ptr);
    ptr->AddObserver(shared_from_this());
}

void my::BridgeEvent::AllDelete(void) {
    _for_bridge_event_actors.clear();
    this->OnNotify("EnemyDead", nullptr);
    for (auto actor : _for_bridge_event_actors) {
        actor->End();
    } // for
}