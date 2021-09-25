#include "Queen.h"

#include "../../Component/VelocityComponent.h"
#include "../../Event/EventManager.h"
#include "../../Event/EventReferenceTable.h"
#include "../../Event/BridgeEvent.h"


ratchet::actor::character::Queen::Queen() :
    super(),
    _event_activated(false) {
}

ratchet::actor::character::Queen::~Queen() {
}

bool ratchet::actor::character::Queen::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);
    return true;
}

bool ratchet::actor::character::Queen::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

void ratchet::actor::character::Queen::Talk(void) {
    auto message = ratchet::game::gamesystem::text::TextSystemMessage();


    if (_event_activated) {
        message.type = decltype(message.type)::QueenFreeTalkTextEvent;
        super::GetTextSystemMessageSubject()->Notify(message);
    } // if
    else {
        message.type = decltype(message.type)::QueenTextEvent;

        message.on_close = [&]() {
            if (auto e = event::EventReferenceTable::Singleton().Get<std::shared_ptr<event::EventManager> >("EventManager")) {
                auto bridge_event = e->CreateGameEvent<event::BridgeEvent>();
                bridge_event->Initialize();
            } // if
            return true;
        };
        super::GetTextSystemMessageSubject()->Notify(message);
        _event_activated = true;
    } // else
}