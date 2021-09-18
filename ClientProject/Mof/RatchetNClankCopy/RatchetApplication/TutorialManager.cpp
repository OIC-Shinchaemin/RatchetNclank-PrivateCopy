#include "TutorialManager.h"

#include "Event/EventReferenceTable.h"
#include "Actor/Gimmick/Wall.h"
#include "Stage/Gimmick/Elevator.h"


void tutorial::TutorialManager::Liberation(TutorialType type) {
    auto index = static_cast<int>(type);
    _flags.at(index) = true;
}

void tutorial::TutorialManager::Complete(void) {
    auto wall_1 = ratchet::event::EventReferenceTable::Singleton().
        Get<std::shared_ptr<ratchet::actor::gimmick::Wall>>("wall_1");
    wall_1->End();
    auto wall_2 = ratchet::event::EventReferenceTable::Singleton().
        Get<std::shared_ptr<ratchet::actor::gimmick::Wall>>("wall_2");
    wall_2->End();


    auto elevator = ratchet::event::EventReferenceTable::Singleton().
        Get<std::shared_ptr<Elevator>>("elevator");
    elevator->SetShow(true);
}