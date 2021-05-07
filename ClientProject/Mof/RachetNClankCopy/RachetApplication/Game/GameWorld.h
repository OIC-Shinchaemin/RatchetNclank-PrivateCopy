#ifndef MY_GAME_WORLD_H
#define MY_GAME_WORLD_H


#include <memory>
#include <vector>

#include "../Actor.h"


namespace my {
class GameWorld {
    using ActorPtr = std::shared_ptr<my::Actor>;
private:
    //! ����
    std::vector<ActorPtr> _actors;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameWorld();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameWorld();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    my::GameWorld::ActorPtr GetActor(uint32_t index) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="actor"></param>
    void AddActor(const ActorPtr& actor);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="actor"></param>
    void RemoveActor(const ActorPtr& actor);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    void UpdateDebug(void);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !MY_GAME_WORLD_H