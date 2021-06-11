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
    GameQuest(rachet::GameQuest::Type type);
    /// <summary>
    /// ��r
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator==(const rachet::GameQuest& obj) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool IsEqual(const rachet::GameQuest& obj) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    rachet::GameQuest::Type GetType(void) const;
};
}
#endif // !RACHET_GAME_QUEST_H