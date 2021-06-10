#ifndef MY_OMNI_WRENCH_H
#define MY_OMNI_WRENCH_H


#include "Weapon.h"


namespace my {
class OmniWrench : public my::Weapon {
    using super = my::Weapon;
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
    virtual bool Initialize(my::Actor::Param* param) override;
};
}
#endif // !MY_OMNI_WRENCH_H