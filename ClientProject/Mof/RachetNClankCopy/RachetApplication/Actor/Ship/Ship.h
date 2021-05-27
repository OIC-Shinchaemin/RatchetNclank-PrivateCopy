#ifndef MY_SHIP_H
#define MY_SHIP_H


#include "../../Actor.h"


namespace my {
class Ship : public my::Actor {
    using super = my::Actor;
public:
    enum class MotionType {
        Default,
        V4,
        CountMax,
    };
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Ship();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Ship();
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="builder"></param>
    virtual void Construct(const std::shared_ptr<class IBuilder>& builder) override;
};
}
#endif // !MY_SHIP_H