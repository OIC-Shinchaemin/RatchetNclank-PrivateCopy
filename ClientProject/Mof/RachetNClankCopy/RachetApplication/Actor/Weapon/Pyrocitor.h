#ifndef RACHET_PYROCITOR_H
#define RACHET_PYROCITOR_H


#include "Mechanical.h"


namespace rachet {
class Pyrocitor : public rachet::Mechanical {
    using super = rachet::Mechanical;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Pyrocitor();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Pyrocitor();
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
#endif // !RACHET_PYROCITOR_H