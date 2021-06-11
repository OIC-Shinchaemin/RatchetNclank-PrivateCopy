#include "GameQuest.h"


ratchet::game::gamesystem::GameQuest::GameQuest() :
    _type() {
}

ratchet::game::gamesystem::GameQuest::GameQuest(ratchet::game::gamesystem::GameQuest::Type type) :
    _type(type) {
}

bool ratchet::game::gamesystem::GameQuest::operator==(const ratchet::game::gamesystem::GameQuest& obj) const {
    return this->_type == obj._type;
}

bool ratchet::game::gamesystem::GameQuest::IsEqual(const ratchet::game::gamesystem::GameQuest& obj) const {
    return *this == obj;
}

ratchet::game::gamesystem::GameQuest::Type ratchet::game::gamesystem::GameQuest::GetType(void) const {
    return this->_type;
}