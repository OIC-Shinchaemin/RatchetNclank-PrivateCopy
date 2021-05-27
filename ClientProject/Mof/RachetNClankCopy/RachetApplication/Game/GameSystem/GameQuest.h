#ifndef MY_GAME_QUEST_H
#define MY_GAME_QUEST_H

namespace my {
class GameQuest {
public:
    enum class Type {
        EnemyDestroy,
        GoHome,
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
    GameQuest(my::GameQuest::Type type);
    /// <summary>
    /// 比較
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator==(const my::GameQuest& obj) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool IsEqual(const my::GameQuest& obj) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::GameQuest::Type GetType(void) const;
};
}
#endif // !MY_GAME_QUEST_H