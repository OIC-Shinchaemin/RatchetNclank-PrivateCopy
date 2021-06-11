#ifndef RACHET_BLASTER_H
#define RACHET_BLASTER_H


#include "Mechanical.h"


namespace rachet {
class Blaster : public rachet::Mechanical {
    using super = rachet::Mechanical;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Blaster();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Blaster();
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
#endif // !RACHET_BLASTER_H