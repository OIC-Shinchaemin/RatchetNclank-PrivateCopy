#ifndef RATCHET_GAME_GAME_SYSTEM_GAME_QUEST_H
#define RATCHET_GAME_GAME_SYSTEM_GAME_QUEST_H


namespace ratchet::game::gamesystem {
class GameQuest {
public:
    enum class Type {
        ToFront,
        EnemyDestroy,
        GoHome,
        ShopAccessStart,
        ShopAccessEnd,
    };
private:
    //! �^�C�v
    GameQuest::Type _type;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameQuest();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="type"></param>
    GameQuest(ratchet::game::gamesystem::GameQuest::Type type);
    /// <summary>
    /// ��r
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator==(const ratchet::game::gamesystem::GameQuest& obj) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool IsEqual(const ratchet::game::gamesystem::GameQuest& obj) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::game::gamesystem::GameQuest::Type GetType(void) const;
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_GAME_QUEST_H