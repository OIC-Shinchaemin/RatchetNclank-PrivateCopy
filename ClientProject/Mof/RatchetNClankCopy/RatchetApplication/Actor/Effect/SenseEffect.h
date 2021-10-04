#ifndef RATCHET_ACTOR_EFFECT_SENSE_EFFECT_H
#define RATCHET_ACTOR_EFFECT_SENSE_EFFECT_H


#include "../Actor.h"

#include <Mof.h>

#include "../../Component/SightRecognitionComponent.h"


namespace ratchet::actor::effect {
class SenseEffect :
    public ratchet::actor::Actor,
    public FindEnemyMessageListener {
    using super = ratchet::actor::Actor;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SenseEffect();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SenseEffect();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const FindEnemyMessage& message) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_ACTOR_EFFECT_SENSE_EFFECT_H