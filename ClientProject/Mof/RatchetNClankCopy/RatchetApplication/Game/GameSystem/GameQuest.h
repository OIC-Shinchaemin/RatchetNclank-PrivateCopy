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
    //! タイプ
    GameQuest::Type _type;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameQuest();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="type"></param>
    GameQuest(ratchet::game::gamesystem::GameQuest::Type type);
    /// <summary>
    /// 比較
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator==(const ratchet::game::gamesystem::GameQuest& obj) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool IsEqual(const ratchet::game::gamesystem::GameQuest& obj) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::game::gamesystem::GameQuest::Type GetType(void) const;
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_GAME_QUEST_H