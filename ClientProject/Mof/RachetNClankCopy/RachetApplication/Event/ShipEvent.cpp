#include "ShipEvent.h"

#include "../Factory/FactoryManager.h"
#include "../Actor//Ship/Ship.h"
#include "../Component/Ship/ShipLandingComponent.h"
#include "../Event/EventReferenceTable.h"
#include "../Component/CameraComponent.h"


my::ShipEvent::ShipEvent() :
    super(),
    _ship_event_subject(),
    _ship_view_camera(),
    _ship_view_camera_controller(),
    _ideal_position() {

    _ship_view_camera_controller.SetAzimuth(0.0f);
    _ship_view_camera_controller.SetAltitude(0.0f);
}

my::ShipEvent::~ShipEvent() {
}

void my::ShipEvent::OnNotify(const char* type, const std::shared_ptr<StageObject>& ptr) {
    if (type == "BridgeActionEnd") {
        // ship
        auto param = my::Actor::Param();
        param.transform.position = Mof::CVector3(10.0f, 9.0f, -25.0f);
        param.name = "ship";
        auto ship = my::FactoryManager::Singleton().CreateActor<my::Ship>("../Resource/builder/ship.json", &param);
        auto com = my::EventReferenceTable::Singleton().Get<std::shared_ptr<my::CameraComponent>>("CameraComponent");
        //ship->GetComponent<my::ShipLandingComponent>()->AddObserver(com);
        ship->GetComponent<my::ActionComponent>()->GetComponent<my::ShipLandingComponent>()->AddObserver(com);
        

        //! ゲームイベント
        _ship_event_subject.Notify("AddRequest", ship);
        _ship_view_camera_controller.RegisterGlobalCamera();
        _ship_view_camera_controller.SetInfo(_info);
    } // if
}

void my::ShipEvent::OnNotify(const my::CameraController::CameraInfo& info) {
    puts("ShipEvent::OnNotify const my::CameraController::CameraInfo& info");
    this->_info = info;

    _info.target_position = Mof::CVector3(10.0f, -4.0f, -25.0f);
    _info.start_position = info.start_position;
    _info.camera_front = info.camera_front;
    _ship_view_camera_controller.SetInfo(_info);
}

my::Observable<const char*, const std::shared_ptr<my::Actor>&>* my::ShipEvent::GetShipEventSubject(void) {
    return &this->_ship_event_subject;
}

bool my::ShipEvent::Initialize(void) {
    _ideal_position = Mof::CVector3();

    _ship_view_camera = std::make_shared<my::Camera>();
    _ship_view_camera->Initialize();
    _ship_view_camera->Update();
    _ship_view_camera_controller.SetCamera(_ship_view_camera);
    _ship_view_camera->Update();
    return true;
}

bool my::ShipEvent::Update(float delta_time) {
    auto info = my::CameraController::CameraInfo();
    info.ideal_position = Mof::CVector3();
    _ship_view_camera_controller.Update(delta_time, info);
    return true;
}