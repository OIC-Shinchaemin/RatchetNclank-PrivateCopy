#ifndef RACHET_BOMB_GLOVE_EFFECT_H
#define RACHET_BOMB_GLOVE_EFFECT_H


#include "ParticleEffect.h"

#include <Mof.h>


namespace rachet {
class BombGloveEffect : public rachet::ParticleEffect {
    using super = rachet::ParticleEffect;
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
    //virtual void Start(const rachet::ParticleEffect::Info& info);
};
}
#endif // !RACHET_BOMB_GLOVE_EFFECT_H