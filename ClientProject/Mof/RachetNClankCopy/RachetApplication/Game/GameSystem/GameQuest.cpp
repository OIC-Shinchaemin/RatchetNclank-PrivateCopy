#include "GameQuest.h"


ratchet::GameQuest::GameQuest() :
    _type() {
}

ratchet::GameQuest::GameQuest(ratchet::GameQuest::Type type) :
    _type(type) {
}

bool ratchet::GameQuest::operator==(const ratchet::GameQuest& obj) const {
    return this->_type == obj._type;
}

bool ratchet::GameQuest::IsEqual(const ratchet::GameQuest& obj) const {
    return *this == obj;
}

ratchet::GameQuest::Type ratchet::GameQuest::GetType(void) const {
    return this->_type;
}