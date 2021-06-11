#ifndef RATCHET_GAME_QUEST_H
#define RATCHET_GAME_QUEST_H


namespace ratchet {
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
    GameQuest(ratchet::GameQuest::Type type);
    /// <summary>
    /// 比較
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator==(const ratchet::GameQuest& obj) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool IsEqual(const ratchet::GameQuest& obj) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::GameQuest::Type GetType(void) const;
};
}
#endif // !RATCHET_GAME_QUEST_H