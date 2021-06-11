#ifndef RATCHET_ACTOR_WEAPON_BOMB_GLOVEL_H
#define RATCHET_ACTOR_WEAPON_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace ratchet {
namespace actor {
namespace weapon {
class BombGlove  : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BombGlove();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BombGlove();
    /// <summary>
    /// ���͔���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsAction(void) const override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform) override;
};
}
}
}
#endif // !RATCHET_ACTOR_WEAPON_BOMB_GLOVEL_H