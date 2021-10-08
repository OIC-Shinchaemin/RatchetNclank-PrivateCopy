#ifndef RATCHET_ACTOR_WEAPON_BLASTER_H
#define RATCHET_ACTOR_WEAPON_BLASTER_H


#include "Mechanical.h"


namespace ratchet::actor::weapon {
class Blaster : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
private:
    //! �e�̑傫��
    float _bullet_scale;
    //! �g�咆
    bool _scaling;
    //! �g�嗦
    float _scaling_maltiply;
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
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform) override;
    /// <summary>
    /// �g��
    /// </summary>
    /// <param name=""></param>
    virtual void Scaling(void) override;
};
}
#endif // !RATCHET_ACTOR_WEAPON_BLASTER_H