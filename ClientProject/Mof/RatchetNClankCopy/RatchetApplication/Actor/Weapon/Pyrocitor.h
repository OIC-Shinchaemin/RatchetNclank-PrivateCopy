#ifndef RATCHET_ACTOR_WEAPON_PYROCITOR_H
#define RATCHET_ACTOR_WEAPON_PYROCITOR_H


#include "Mechanical.h"


namespace ratchet {
namespace actor {
namespace weapon {
class Pyrocitor : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Pyrocitor();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Pyrocitor();
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
#endif // !RATCHET_ACTOR_WEAPON_PYROCITOR_H