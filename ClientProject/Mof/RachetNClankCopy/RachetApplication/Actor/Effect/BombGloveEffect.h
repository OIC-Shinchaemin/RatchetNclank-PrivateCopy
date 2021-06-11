#ifndef RACHET_BOMB_GLOVE_EFFECT_H
#define RACHET_BOMB_GLOVE_EFFECT_H


#include "ParticleEffect.h"

#include <Mof.h>


namespace rachet {
class BombGloveEffect : public rachet::ParticleEffect {
    using super = rachet::ParticleEffect;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BombGloveEffect();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGloveEffect();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    //virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    //virtual bool Render(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name="info"></param>
    //virtual void Start(const rachet::ParticleEffect::Info& info);
};
}
#endif // !RACHET_BOMB_GLOVE_EFFECT_H