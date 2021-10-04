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
    /// �R���X�g���N�^
    /// </summary>
    SenseEffect();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SenseEffect();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const FindEnemyMessage& message) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_ACTOR_EFFECT_SENSE_EFFECT_H