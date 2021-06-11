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
    //virtual void Start(const ratchet::ParticleEffect::Info& info);
};
}
}
}
#endif // !RATCHET_ACTOR_EFFECT_BOMB_GLOVE_EFFECT_H