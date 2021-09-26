#ifndef RATCHET_ACTOR_FACILITY_BARRACK_H
#define RATCHET_ACTOR_FACILITY_BARRACK_H


#include "../Actor.h"


namespace ratchet::actor::facility {
class Barrack : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Barrack();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Barrack();
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
#endif // !RATCHET_ACTOR_FACILITY_BARRACK_H