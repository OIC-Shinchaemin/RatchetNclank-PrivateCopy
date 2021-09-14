#ifndef RATCHET_ACTOR_EFFECT_BOMB_GLOVE_EFFECT_H
#define RATCHET_ACTOR_EFFECT_BOMB_GLOVE_EFFECT_H


#include "ParticleEffect.h"

#include <Mof.h>


namespace ratchet::actor::effect {
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
};
}
#endif // !RATCHET_ACTOR_EFFECT_BOMB_GLOVE_EFFECT_H