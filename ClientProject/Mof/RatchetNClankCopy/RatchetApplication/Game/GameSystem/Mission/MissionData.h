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
    //! タイプ
    MissionType type;
};
class MissionData {
private:
    //! パラメータ
    MissionDataParam _param;
public:
    //! ゲッター
    base::accessor::Getter<decltype(_param.type)> type = (_param.type);
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MissionData();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~MissionData();
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_DATA_H