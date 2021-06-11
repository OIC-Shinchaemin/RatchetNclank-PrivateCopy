#include "ShipEvent.h"

#include "../Factory/FactoryManager.h"
#include "../Actor//Ship/Ship.h"
#include "../Component/Ship/ShipLandingComponent.h"
#include "../Event/EventReferenceTable.h"
#include "../Component/CameraComponent.h"


ratchet::event::ShipEvent::ShipEvent() :
    super(),
    _ship_event_subject(),
    _ship_view_camera(),
    _ship_view_camera_controller(),
    _ideal_position() {

    _ship_view_camera_controller.SetAzimuth(0.0f);
    _ship_view_camera_controller.SetAltitude(0.0f);
}

ratchet::event::ShipEvent::~ShipEvent() {
}

void ratchet::event::ShipEvent::OnNotify(const char* type, const std::shared_ptr<StageObject>& ptr) {
    if (type == "BridgeActionEnd") {
        // ship
        auto param = ratchet::Actor::Param();
        param.transform.position = Mof::CVector3(10.0f, 9.0f, -25.0f);
        param.name = "ship";
        auto ship = ratchet::FactoryManager::Singleton().CreateActor<ratchet::Ship>("../Resource/builder/ship.json", &param);
        auto com = ratchet::event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::CameraComponent>>("CameraComponent");
        //ship->GetComponent<ratchet::ShipLandingComponent>()->AddObserver(com);
        ship->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::ShipLandingComponent>()->AddObserver(com);
        

        //! ゲームイベント
        _ship_event_subject.Notify("AddRequest", ship);
        _ship_view_camera_controller.RegisterGlobalCamera();
        _ship_view_camera_controller.SetInfo(_info);
    } // if
}

void ratchet::event::ShipEvent::OnNotify(const ratchet::camera::CameraController::CameraInfo& info) {
    puts("ShipEvent::OnNotify const ratchet::CameraController::CameraInfo& info");
    this->_info = info;

    _info.target_position = Mof::CVector3(10.0f, -4.0f, -25.0f);
    _info.start_position = info.start_position;
    _info.camera_front = info.camera_front;
    _ship_view_camera_controller.SetInfo(_info);
}

base::core::Observable<const char*, const std::shared_ptr<ratchet::Actor>&>* ratchet::event::ShipEvent::GetShipEventSubject(void) {
    return &this->_ship_event_subject;
}

bool ratchet::event::ShipEvent::Initialize(void) {
    _ideal_position = Mof::CVector3();

    _ship_view_camera = std::make_shared<ratchet::camera::Camera>();
    _ship_view_camera->Initialize();
    _ship_view_camera->Update();
    _ship_view_camera_controller.SetCamera(_ship_view_camera);
    _ship_view_camera->Update();
    return true;
}

bool ratchet::event::ShipEvent::Update(float delta_time) {
    auto info = ratchet::camera::CameraController::CameraInfo();
    info.ideal_position = Mof::CVector3();
    _ship_view_camera_controller.Update(delta_time, info);
    return true;
}