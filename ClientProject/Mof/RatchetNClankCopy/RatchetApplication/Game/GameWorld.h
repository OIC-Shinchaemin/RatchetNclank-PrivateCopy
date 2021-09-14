#ifndef RATCHET_GAME_GAME_WORLD_H
#define RATCHET_GAME_GAME_WORLD_H


#include <memory>
#include <vector>

#include "../Actor/Actor.h"


namespace ratchet::game {
class GameWorld {
    using ActorPtr = std::shared_ptr<ratchet::actor::Actor>;
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
    ratchet::game::GameWorld::ActorPtr GetActor(uint32_t index) const;
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
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
#endif // !RATCHET_GAME_GAME_WORLD_H