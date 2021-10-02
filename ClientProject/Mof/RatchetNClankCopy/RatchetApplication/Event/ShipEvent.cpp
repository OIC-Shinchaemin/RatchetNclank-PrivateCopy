#include "ShipEvent.h"

#include "../Factory/FactoryManager.h"
#include "../Actor/Vehicle/Ship.h"
#include "../Component/Ship/ShipLandingComponent.h"
#include "../Event/EventReferenceTable.h"
#include "../Component/CameraComponent.h"
#include "../Actor/Character/Player.h"
#include "../Event/EventReferenceTable.h"
#include "../Component/CameraComponent.h"


ratchet::event::ShipEvent::ShipEvent() :
    super(),
    _start(false),
    _ship_event_subject(),
    _ship_view_camera(),
    _ship_view_camera_controller(),
    _ideal_position(),
    _timer(),
    _time(2.0f) ,
    _ship_generate_position(Mof::CVector3(10.0f, 9.0f, -25.0f)){

    _ship_view_camera_controller.SetAzimuth(0.0f);
    _ship_view_camera_controller.SetAltitude(0.0f);
}

ratchet::event::ShipEvent::~ShipEvent() {
}

void ratchet::event::ShipEvent::OnNotify(const char* type, const std::shared_ptr<StageObject>& ptr) {
    if (type == "BridgeActionEnd") {
        _start = true;
        // ship
        auto param = ratchet::actor::Actor::Param();
        param.transform.position = _ship_generate_position;
        param.name = "ship";
        auto ship = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::vehicle::Ship>("../Resource/builder/ship.json", &param);
        auto com = ratchet::event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::component::CameraComponent>>("CameraComponent");
        ship->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::ship::ShipLandingComponent>()->AddObserver(com);

        //! ゲームイベント
        _ship_event_subject.Notify("AddRequest", ship);
        _ship_view_camera_controller.RegisterGlobalCamera();



        _info.target_position = Mof::CVector3(10.0f, -4.0f, -25.0f);
        _info.start_position = ::CGraphicsUtilities::GetCamera()->GetViewPosition();
        _info.ideal_position = ::CGraphicsUtilities::GetCamera()->GetViewPosition();
        _info.camera_front = ::CGraphicsUtilities::GetCamera()->GetViewFront();
        _ship_view_camera_controller.SetInfo(_info);
        _ship_view_camera->Update();

        _timer.Initialize(_time, false);
    } // if
}

void ratchet::event::ShipEvent::OnNotify(const ratchet::camera::CameraController::CameraInfo& info) {
    /*
    puts("ShipEvent::OnNotify const ratchet::CameraController::CameraInfo& info");
    this->_info = info;

    _info.target_position = Mof::CVector3(10.0f, -4.0f, -25.0f);
    _info.start_position = info.start_position;
    _info.camera_front = info.camera_front;
    _ship_view_camera_controller.SetInfo(_info);
    */
}

base::core::Observable<const char*, const std::shared_ptr<ratchet::actor::Actor>&>* ratchet::event::ShipEvent::GetShipEventSubject(void) {
    return &this->_ship_event_subject;
}

bool ratchet::event::ShipEvent::Initialize(void) {
    _ideal_position = Mof::CVector3();

    _ship_view_camera = std::make_shared<ratchet::camera::Camera>();
    _ship_view_camera->Initialize();
    _ship_view_camera_controller.SetCamera(_ship_view_camera);
    _ship_view_camera->Update();
    return true;
}

bool ratchet::event::ShipEvent::Update(float delta_time) {
    if (!_start) {
        return false;
    } // if
    if (_timer.Tick(delta_time)) {
        auto player = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player> >("player");
        if (player) {
            auto dir = _ship_generate_position - player->GetPosition();
            float angle_y = std::atan2f(-dir.z, dir.x) + math::kHalfPi;

            auto camera_com = player->GetComponent<component::CameraComponent>();
            auto camera_controller = camera_com->GetCameraController()->GetService();
            camera_controller->RegisterGlobalCamera();
            camera_controller->SetAzimuth(math::ToDegree(angle_y));
        } // if


        _ship_event_end_message_subject.Notify({});

        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
        return true;
    } // if
    auto info = ratchet::camera::CameraController::CameraInfo();
    info.ideal_position = Mof::CVector3();
    _ship_view_camera_controller.Update(delta_time, info);
    return true;
}