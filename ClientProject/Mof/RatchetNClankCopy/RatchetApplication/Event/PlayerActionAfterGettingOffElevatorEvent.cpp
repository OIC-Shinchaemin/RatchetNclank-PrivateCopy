#include "PlayerActionAfterGettingOffElevatorEvent.h"

#include "EventReferenceTable.h"
#include "../Actor/Actor.h"
#include "../Actor/Character/Player.h"
#include "../Component/ActionStateComponent.h"
#include "../State/PlayerActionStateDefine.h"
#include "PlayerActionAfterGettingOffElevatorEvent.h"


ratchet::event::PlayerActionAfterGettingOffElevatorEvent::PlayerActionAfterGettingOffElevatorEvent() :
    super(),
    _active(),
    _time_set(3.0f),
    _timer() {
    _timer.Initialize(_time_set, false);
}

ratchet::event::PlayerActionAfterGettingOffElevatorEvent::~PlayerActionAfterGettingOffElevatorEvent() {
}

void ratchet::event::PlayerActionAfterGettingOffElevatorEvent::OnNotify(const ratchet::event::EnemyViewEventEndMessage& message) {
    _active = true;
}

bool ratchet::event::PlayerActionAfterGettingOffElevatorEvent::Initialize(void) {
    return true;
}

bool ratchet::event::PlayerActionAfterGettingOffElevatorEvent::Update(float delta_time) {
    if (!_active) {
        return false;
    } // if

    if (_timer.Tick(delta_time)) {
        /*
        return true;
        auto action_event = new event::PlayerActionAfterGettingOffElevatorEvent();
        if (event::EventReferenceTable::Singleton().Exist("player")) {
            auto player = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player>>("player");
            auto action = player->GetComponent<ratchet::component::ActionStateComponent>();
            action->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackOneState);
        } // if
        return true;
        */
    } // if
    return false;
}