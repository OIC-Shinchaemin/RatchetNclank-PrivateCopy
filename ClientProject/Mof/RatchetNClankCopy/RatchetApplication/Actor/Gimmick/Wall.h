#ifndef RATCHET_ACTOR_GIMMICK_WALL_H
#define RATCHET_ACTOR_GIMMICK_WALL_H


#include "../Actor.h"


namespace ratchet::actor::gimmick {
class Wall : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Wall();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Wall();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_ACTOR_GIMMICK_WALL_H