#include "MissionSystem.h"


ratchet::game::gamesystem::mission::MissionSystem::MissionSystem() :
    _current_mission(){
}

ratchet::game::gamesystem::mission::MissionSystem::~MissionSystem() {
}

bool ratchet::game::gamesystem::mission::MissionSystem::Reception(const game::gamesystem::mission::MissionData& mission) {
    _current_mission = mission;
    return true;
}