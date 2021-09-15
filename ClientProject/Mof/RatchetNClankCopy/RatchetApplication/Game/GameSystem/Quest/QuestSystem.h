#ifndef RATCHET_GAME_GAME_SYSTEM_QUEST_QUEST_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_QUEST_QUEST_SYSTEM_H


#include <optional>

#include "../GameQuest.h"


namespace ratchet::game::gamesystem::quest {
class QuestSystem {
private:
    //! 現在のクエスト
    std::optional<ratchet::game::gamesystem::GameQuest> _current_quest;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    QuestSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~QuestSystem();
    /// <summary>
    /// 受付
    /// </summary>
    /// <returns></returns>
    bool Reception(const game::gamesystem::GameQuest& quest);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_QUEST_QUEST_SYSTEM_H