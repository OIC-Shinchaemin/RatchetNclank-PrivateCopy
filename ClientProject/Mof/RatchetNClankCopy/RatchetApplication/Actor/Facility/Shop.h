#ifndef RATCHET_ACTOR_FACILITY_SHOP_H
#define RATCHET_ACTOR_FACILITY_SHOP_H


#include "../Actor.h"


namespace ratchet::actor::facility{
class Shop : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Shop();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Shop();
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
#endif // !RATCHET_ACTOR_FACILITY_SHOP_H