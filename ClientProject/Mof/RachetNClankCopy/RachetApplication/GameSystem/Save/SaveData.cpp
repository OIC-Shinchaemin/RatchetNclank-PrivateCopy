#include "SaveData.h"

#include <type_traits>


my::SaveData::SaveData() :
    _param() {
}

my::SaveData::~SaveData() {
}

void my::SaveData::MoveParam(SaveDataParam& param) {
    this->_param = std::move(param);
}

uint32_t my::SaveData::GetMoney(void) const {
    return this->_param.money;
}

const std::vector<std::string>& my::SaveData::GetAvailableWeaponsAddress(void) {
    return this->_param.available_weapons;
}
