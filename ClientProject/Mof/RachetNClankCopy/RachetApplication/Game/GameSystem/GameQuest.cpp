#include "GameQuest.h"


my::GameQuest::GameQuest() :
    _type() {
}

my::GameQuest::GameQuest(my::GameQuest::Type type) :
    _type(type) {
}

bool my::GameQuest::operator==(const my::GameQuest& obj) const {
    return this->_type == obj._type;
}

bool my::GameQuest::IsEqual(const my::GameQuest& obj) const {
    return *this == obj;
}

my::GameQuest::Type my::GameQuest::GetType(void) const {
    return this->_type;
}