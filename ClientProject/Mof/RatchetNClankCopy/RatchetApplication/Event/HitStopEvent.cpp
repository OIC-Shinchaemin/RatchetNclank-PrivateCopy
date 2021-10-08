#include "HitStopEvent.h"


ratchet::event::HitStopEvent::HitStopEvent() :
    _time(0.2f),
    _timer(),
    _game_scene() {
}

ratchet::event::HitStopEvent::~HitStopEvent() {
}

bool ratchet::event::HitStopEvent::Initialize(void) {
    _game_scene.lock()->SetState(decltype(_game_scene.lock()->GetState())::Pause);
    _timer.Initialize(_time, false);
    return true;
}

bool ratchet::event::HitStopEvent::Update(float delta_time) {
    if (_timer.Tick(delta_time)) {
        _game_scene.lock()->SetState( decltype(_game_scene.lock()->GetState())::Active);
        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}