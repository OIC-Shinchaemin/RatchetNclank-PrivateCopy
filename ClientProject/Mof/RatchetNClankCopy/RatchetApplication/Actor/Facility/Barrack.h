#ifndef RATCHET_ACTOR_FACILITY_BARRACK_H
#define RATCHET_ACTOR_FACILITY_BARRACK_H


#include "../Actor.h"


namespace ratchet::actor::facility {
class Barrack : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Barrack();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Barrack();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_ACTOR_FACILITY_BARRACK_H