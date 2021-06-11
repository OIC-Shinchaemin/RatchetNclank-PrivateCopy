#ifndef RATCHET_SHOP_H
#define RATCHET_SHOP_H


#include "../../Actor.h"


namespace ratchet {
class Shop : public ratchet::Actor {
    using super = ratchet::Actor;
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
#endif // !RATCHET_SHOP_H