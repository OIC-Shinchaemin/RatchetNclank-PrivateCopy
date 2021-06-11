#ifndef RATCHET_OMNI_WRENCH_H
#define RATCHET_OMNI_WRENCH_H


#include "Weapon.h"


namespace ratchet {
class OmniWrench : public ratchet::Weapon {
    using super = ratchet::Weapon;
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
    virtual bool Initialize(ratchet::Actor::Param* param) override;
};
}
#endif // !RATCHET_OMNI_WRENCH_H