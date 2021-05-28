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
    GameQuest(my::GameQuest::Type type);
    /// <summary>
    /// ��r
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator==(const my::GameQuest& obj) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool IsEqual(const my::GameQuest& obj) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::GameQuest::Type GetType(void) const;
};
}
#endif // !MY_GAME_QUEST_H