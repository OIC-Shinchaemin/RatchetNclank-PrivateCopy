#ifndef RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_SYSTEM_H

    
#include <optional>

#include "MissionData.h"


namespace ratchet::game::gamesystem::mission {
class MissionSystem {
private:
    //! ���݂̃~�b�V����
    std::optional<ratchet::game::gamesystem::mission::MissionData> _current_mission;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MissionSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~MissionSystem();
    /// <summary>
    /// ��t
    /// </summary>
    /// <returns></returns>
    bool Reception(const game::gamesystem::mission::MissionData& mission);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_SYSTEM_H