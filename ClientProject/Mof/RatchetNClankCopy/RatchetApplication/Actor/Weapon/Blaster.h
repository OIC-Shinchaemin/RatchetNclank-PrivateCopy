#ifndef RATCHET_ACTOR_WEAPON_BLASTER_H
#define RATCHET_ACTOR_WEAPON_BLASTER_H


#include "Mechanical.h"


namespace ratchet::actor::weapon {
class Blaster : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
private:
    //! �e�̑傫��
    float _bullet_scale;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Blaster();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Blaster();
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
#endif // !RATCHET_ACTOR_WEAPON_BLASTER_H