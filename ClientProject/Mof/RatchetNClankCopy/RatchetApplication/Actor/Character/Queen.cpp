#include "Queen.h"

#include "../../Component/VelocityComponent.h"
#include "../../Event/EventManager.h"
#include "../../Event/EventReferenceTable.h"
#include "../../Event/BridgeEvent.h"
#include "../../Light/LightManager.h"
#include "../../Component/BillboardComponent.h"


ratchet::actor::character::Queen::Queen() :
    super(),
    _event_activated(false),
    _light_pillar() {
}

ratchet::actor::character::Queen::~Queen() {
}

bool ratchet::actor::character::Queen::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);


    if (auto light = event::EventReferenceTable::Singleton().Get < std::shared_ptr <  ratchet::light::LightManager> >("LightManager")) {
        auto info = light::LightPillarCreateInfo();

        auto pos = super::GetPosition();
        auto rotate = super::GetRotate();

        float offset = 3.0f;
        auto front = Mof::CVector3(-math::vec3::kUnitZ * offset);
        front.RotationY(rotate.y - math::kHalfPi);
        pos.y -= 10.0f;
        pos += front;

        info.position = pos;
        _light_pillar = light->CreateLightPillar(info);
    } // if
    return true;
}

bool ratchet::actor::character::Queen::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

void ratchet::actor::character::Queen::Talk(void) {
//    auto player = _player.lock();

    auto billboard = super::GetComponent<component::BillboardComponent>();
    auto dir = Mof::CVector3(super::GetPosition() - super::GetTalkedTarget()->GetPosition());
    float angle_y = std::atan2f(-dir.z, dir.x) + math::kHalfPi;
    super::SetRotate(Mof::CVector3(0.0f, angle_y, 0.0f));
    billboard->SetOffsetRotation(-super::GetRotate());


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

                _light_pillar.lock()->Disable();
            } // if
            return true;
        };
        auto billboard = super::GetComponent<component::BillboardComponent>();
        billboard->Inactivate();

        super::GetTextSystemMessageSubject()->Notify(message);
        _event_activated = true;
    } // else
}