#ifndef RATCHET_PYROCITOR_H
#define RATCHET_PYROCITOR_H


#include "Mechanical.h"


namespace ratchet {
class Pyrocitor : public ratchet::Mechanical {
    using super = ratchet::Mechanical;
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
#endif // !RATCHET_PYROCITOR_H