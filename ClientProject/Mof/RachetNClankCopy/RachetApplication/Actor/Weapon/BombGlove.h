#ifndef RACHET_BOMB_GLOVEL_H
#define RACHET_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace rachet {
class BombGlove  : public rachet::Mechanical {
    using super = rachet::Mechanical;
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
#endif // !RACHET_BOMB_GLOVEL_H