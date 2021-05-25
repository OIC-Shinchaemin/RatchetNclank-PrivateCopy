#include "ShipEvent.h"

#include "../Factory/FactoryManager.h"
#include "../Actor//Ship/Ship.h"


my::ShipEvent::ShipEvent() :
    _ship_event_subject() {
}

my::ShipEvent::~ShipEvent() {
}

void my::ShipEvent::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}

void my::ShipEvent::OnNotify(const char* type, const std::shared_ptr<my::BridgeEvent>& ptr) {
    if (type == "BridgeEventActionStart") {
        // ship
        auto param = my::Actor::Param();
        param.transform.position = Mof::CVector3(10.0f, 20.0f, -25.0f);
        param.name = "ship";
        auto ship = my::FactoryManager::Singleton().CreateActor<my::Ship>("../Resource/builder/ship.json", &param);
        //! ゲームイベント
        _ship_event_subject.Notify("AddRequest", ship);
    } // if
}

my::Observable<const char*, const std::shared_ptr<my::Actor>&>& my::ShipEvent::GetShipEventSubject(void) {
    return this->_ship_event_subject;
}