#ifndef MY_BLASTER_H
#define MY_BLASTER_H


#include "Mechanical.h"


namespace my {
class Blaster : public my::Mechanical {
    using super = my::Mechanical;
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
#endif // !MY_BLASTER_H