#include "SaveData.h"

#include <type_traits>


ratchet::game::gamesystem::save::SaveData::SaveData() :
    _param() {
}

ratchet::game::gamesystem::save::SaveData::~SaveData() {
}

void ratchet::game::gamesystem::save::SaveData::MoveParam(SaveDataParam& param) {
    this->_param = std::move(param);
}

uint32_t ratchet::game::gamesystem::save::SaveData::GetMoney(void) const {
    return this->_param.money;
}

const std::vector<std::string>& ratchet::game::gamesystem::save::SaveData::GetAvailableMechanicalWeaponsAddress(void) {
    return this->_param.available_weapons;
}
