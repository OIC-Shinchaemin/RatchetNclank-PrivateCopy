#include "QuestSystem.h"

#include "Base/Core/Header.h"
#include "Base/Core/Utility.h"


ratchet::game::gamesystem::quest::QuestSystem::QuestSystem() {
}

ratchet::game::gamesystem::quest::QuestSystem::~QuestSystem() {
}

bool ratchet::game::gamesystem::quest::QuestSystem::Reception(const game::gamesystem::GameQuest& quest) {
    _current_quest = quest;
    return true;
}