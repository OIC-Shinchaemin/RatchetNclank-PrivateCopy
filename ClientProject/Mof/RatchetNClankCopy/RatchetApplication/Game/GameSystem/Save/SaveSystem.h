#ifndef RATCHET_GAME_GAME_SYSTEM_SAVE_SAVE_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_SAVE_SAVE_SYSTEM_H


#include <string>

#include "SaveData.h"


namespace ratchet::game::gamesystem::save {
class SaveSystem {
private:
    std::string _path;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SaveSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SaveSystem();
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="out"></param>
    /// <returns></returns>
    bool Fetch(ratchet::game::gamesystem::save::SaveData& out);
    /// <summary>
    /// ��������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    bool Save(const ratchet::game::gamesystem::save::SaveDataParam& param);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SAVE_SAVE_SYSTEM_H