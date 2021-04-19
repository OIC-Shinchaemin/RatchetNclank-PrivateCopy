#ifndef MY_BOMB_GLOVEL_H
#define MY_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace my {
class BombGlove  : public my::Mechanical {
    using super = my::Mechanical;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BombGlove();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGlove();
    /// <summary>
    /// 入力判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsAction(void) const override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform) override;
};
}
#endif // !MY_BOMB_GLOVEL_H