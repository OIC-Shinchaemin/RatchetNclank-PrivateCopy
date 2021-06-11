#ifndef RACHET_GAME_QUEST_H
#define RACHET_GAME_QUEST_H


namespace rachet {
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
    GameQuest(rachet::GameQuest::Type type);
    /// <summary>
    /// 比較
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator==(const rachet::GameQuest& obj) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool IsEqual(const rachet::GameQuest& obj) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    rachet::GameQuest::Type GetType(void) const;
};
}
#endif // !RACHET_GAME_QUEST_H