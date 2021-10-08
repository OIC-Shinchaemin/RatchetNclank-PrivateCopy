#ifndef RATCHET_ACTOR_WEAPON_OMNI_WRENCH_H
#define RATCHET_ACTOR_WEAPON_OMNI_WRENCH_H


#include "Weapon.h"


namespace ratchet::actor::weapon {
class OmniWrench : public ratchet::actor::weapon::Weapon {
    using super = ratchet::actor::weapon::Weapon;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    OmniWrench();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~OmniWrench();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
};
}
#endif // !RATCHET_ACTOR_WEAPON_OMNI_WRENCH_H