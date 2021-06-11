#include "SaveData.h"

#include <type_traits>


ratchet::SaveData::SaveData() :
    _param() {
}

ratchet::SaveData::~SaveData() {
}

void ratchet::SaveData::MoveParam(SaveDataParam& param) {
    this->_param = std::move(param);
}

uint32_t ratchet::SaveData::GetMoney(void) const {
    return this->_param.money;
}

const std::vector<std::string>& ratchet::SaveData::GetAvailableMechanicalWeaponsAddress(void) {
    return this->_param.available_weapons;
}
