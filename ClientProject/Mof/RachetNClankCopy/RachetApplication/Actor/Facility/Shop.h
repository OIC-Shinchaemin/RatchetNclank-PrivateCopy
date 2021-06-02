#ifndef MY_SHOP_H
#define MY_SHOP_H


#include "../../Actor.h"


namespace my {
class Shop : public my::Actor {
    using super = my::Actor;
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
#endif // !MY_SHOP_H