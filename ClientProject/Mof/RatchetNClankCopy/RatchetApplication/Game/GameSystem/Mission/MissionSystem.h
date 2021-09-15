#ifndef RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_SYSTEM_H

    
#include <optional>

#include "MissionData.h"


namespace ratchet::game::gamesystem::mission {
class MissionSystem {
private:
    //! 現在のミッション
    std::optional<ratchet::game::gamesystem::mission::MissionData> _current_mission;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MissionSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~MissionSystem();
    /// <summary>
    /// 受付
    /// </summary>
    /// <returns></returns>
    bool Reception(const game::gamesystem::mission::MissionData& mission);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_MISSION_MISSION_SYSTEM_H