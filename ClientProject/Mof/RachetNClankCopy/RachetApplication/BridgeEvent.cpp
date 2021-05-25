#include "BridgeEvent.h"

my::BridgeEvent::BridgeEvent() :
    _for_bridge_event_actors(),
    _stage() {
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
            for (auto gimmick : _stage->GetGimmickArray()) {
                if (gimmick->GetType() == StageObjectType::Bridge) {
                    gimmick->ActionStart();
                    Observable::Notify("BridgeEventActionStart", shared_from_this());
                } // if
            } // for
        } // if
    } // if
}

void my::BridgeEvent::SetStage(Stage* ptr) {
    this->_stage = ptr;
}

bool my::BridgeEvent::Initialize(void) {
    _for_bridge_event_actors.clear();
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