#ifndef RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_DATA_H
#define RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_DATA_H


#include <cstdint>
#include <string>

#include "Base/Accessor/Getter.h"


namespace ratchet::game::gamesystem::mission {
struct MissionDataParam {
    enum class MissionType {
        GoToBarracks,
        Tutorial_0,
        Tutorial_1,
        Tutorial_2,
        GameClear
    };
    //! �^�C�v
    MissionType type;
};
class MissionData {
private:
    //! �p�����[�^
    MissionDataParam _param;
public:
    //! �Q�b�^�[
    base::accessor::Getter<decltype(_param.type)> type = (_param.type);
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MissionData();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~MissionData();
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_DATA_H