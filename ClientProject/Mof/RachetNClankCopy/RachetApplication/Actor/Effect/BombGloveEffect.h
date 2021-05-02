#ifndef MY_BOMB_GLOVE_EFFECT_H
#define MY_BOMB_GLOVE_EFFECT_H


#include "ParticleEffect.h"

#include <Mof.h>


namespace my {
class BombGloveEffect : public my::ParticleEffect {
    using super = my::ParticleEffect;
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
    //virtual void Start(const my::ParticleEffect::Info& info);
};
}
#endif // !MY_BOMB_GLOVE_EFFECT_H