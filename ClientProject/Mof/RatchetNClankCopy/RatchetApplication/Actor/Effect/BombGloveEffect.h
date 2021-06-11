#ifndef RATCHET_ACTOR_EFFECT_BOMB_GLOVE_EFFECT_H
#define RATCHET_ACTOR_EFFECT_BOMB_GLOVE_EFFECT_H


#include "ParticleEffect.h"

#include <Mof.h>


namespace ratchet {
namespace actor {
namespace effect {
class BombGloveEffect : public ratchet::actor::effect::ParticleEffect {
    using super = ratchet::actor::effect::ParticleEffect;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BombGloveEffect();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BombGloveEffect();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    //virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    //virtual bool Render(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name="info"></param>
    //virtual void Start(const ratchet::ParticleEffect::Info& info);
};
}
}
}
#endif // !RATCHET_ACTOR_EFFECT_BOMB_GLOVE_EFFECT_H