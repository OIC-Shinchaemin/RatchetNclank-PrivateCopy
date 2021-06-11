#ifndef RACHET_SHOP_H
#define RACHET_SHOP_H


#include "../../Actor.h"


namespace rachet {
class Shop : public rachet::Actor {
    using super = rachet::Actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Shop();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Shop();
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
#endif // !RACHET_SHOP_H