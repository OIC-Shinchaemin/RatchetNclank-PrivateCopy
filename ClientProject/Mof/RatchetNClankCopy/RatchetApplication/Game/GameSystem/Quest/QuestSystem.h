#ifndef RATCHET_GAME_GAME_SYSTEM_QUEST_QUEST_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_QUEST_QUEST_SYSTEM_H


#include <optional>

#include "../GameQuest.h"


namespace ratchet::game::gamesystem::quest {
class QuestSystem {
private:
    //! ���݂̃N�G�X�g
    std::optional<ratchet::game::gamesystem::GameQuest> _current_quest;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    QuestSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~QuestSystem();
    /// <summary>
    /// ��t
    /// </summary>
    /// <returns></returns>
    bool Reception(const game::gamesystem::GameQuest& quest);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_QUEST_QUEST_SYSTEM_H