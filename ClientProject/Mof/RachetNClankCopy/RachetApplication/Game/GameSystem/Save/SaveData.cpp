#include "SaveData.h"

#include <type_traits>


rachet::SaveData::SaveData() :
    _param() {
}

rachet::SaveData::~SaveData() {
}

void rachet::SaveData::MoveParam(SaveDataParam& param) {
    this->_param = std::move(param);
}

uint32_t rachet::SaveData::GetMoney(void) const {
    return this->_param.money;
}

const std::vector<std::string>& rachet::SaveData::GetAvailableMechanicalWeaponsAddress(void) {
    return this->_param.available_weapons;
}
