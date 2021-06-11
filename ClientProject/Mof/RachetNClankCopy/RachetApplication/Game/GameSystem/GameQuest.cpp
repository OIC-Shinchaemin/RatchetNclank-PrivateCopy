#include "GameQuest.h"


rachet::GameQuest::GameQuest() :
    _type() {
}

rachet::GameQuest::GameQuest(rachet::GameQuest::Type type) :
    _type(type) {
}

bool rachet::GameQuest::operator==(const rachet::GameQuest& obj) const {
    return this->_type == obj._type;
}

bool rachet::GameQuest::IsEqual(const rachet::GameQuest& obj) const {
    return *this == obj;
}

rachet::GameQuest::Type rachet::GameQuest::GetType(void) const {
    return this->_type;
}