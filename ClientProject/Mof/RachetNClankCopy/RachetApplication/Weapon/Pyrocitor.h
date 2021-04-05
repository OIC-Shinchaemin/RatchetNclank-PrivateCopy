#ifndef MY_PYROCITOR_H
#define MY_PYROCITOR_H


#include "Mechanical.h"


namespace my {
class Pyrocitor : public my::Mechanical {
    using super = my::Mechanical;
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
#endif // !MY_PYROCITOR_H