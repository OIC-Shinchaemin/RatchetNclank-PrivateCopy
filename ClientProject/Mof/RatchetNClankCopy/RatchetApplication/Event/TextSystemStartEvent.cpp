#include "TextSystemStartEvent.h"

#include "../Gamepad.h"


ratchet::event::TextSystemStartEvent::TextSystemStartEvent() :
    super(),
    _timer(),
    _scene(),
    _text_system(){
    _timer.Initialize(1.2f, false, true);
}

void ratchet::event::TextSystemStartEvent::SetGameScene(const std::shared_ptr<ratchet::scene::Scene>& ptr) {
    this->_scene = ptr;
}

void ratchet::event::TextSystemStartEvent::SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem>& ptr) {
    this->_text_system = ptr;
}

bool ratchet::event::TextSystemStartEvent::Initialize(void) {
    return true;
}

bool ratchet::event::TextSystemStartEvent::Update(float delta_time) {
    if (_timer.Tick(delta_time)) {
        if (auto text = _text_system.lock()) {
            text->Activate();
        } // if
        if (auto scene = _scene.lock()) {
            scene->SetState(scene::Scene::State::Pause);
        } // if

        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}