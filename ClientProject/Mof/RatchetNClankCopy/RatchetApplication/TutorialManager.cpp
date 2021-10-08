#include "TutorialManager.h"

#include "Event/EventReferenceTable.h"
#include "Actor/Gimmick/Wall.h"
#include "Stage/Gimmick/Elevator.h"
#include "Game/GameManager.h"
#include "Game/GameSystem/WeaponSystem.h"


void tutorial::TutorialManager::Liberation(TutorialType type) {
    auto index = static_cast<int>(type);
    _flags.at(index) = true;
}

void tutorial::TutorialManager::Complete(void) {
    if (ratchet::event::EventReferenceTable::Singleton().Exist("wall_1")) {
        auto wall_1 = ratchet::event::EventReferenceTable::Singleton().
            Get<std::shared_ptr<ratchet::actor::gimmick::Wall>>("wall_1");
        wall_1->End();
    } // if
    if (ratchet::event::EventReferenceTable::Singleton().Exist("wall_2")) {
        auto wall_2 = ratchet::event::EventReferenceTable::Singleton().
            Get<std::shared_ptr<ratchet::actor::gimmick::Wall>>("wall_2");
        wall_2->End();
    } // if
    if (ratchet::event::EventReferenceTable::Singleton().Exist("elevator")) {
        auto elevator = ratchet::event::EventReferenceTable::Singleton().
            Get<std::shared_ptr<Elevator>>("elevator");
        elevator->SetShow(true);
    } // if

    
    if (ratchet::event::EventReferenceTable::Singleton().Exist("GameManager")) {
        auto game = ratchet::event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::game::GameManager>>("GameManager");
        auto weapon = game->GetWeaponSystem();
        weapon->FullCharge();
    } // if

}