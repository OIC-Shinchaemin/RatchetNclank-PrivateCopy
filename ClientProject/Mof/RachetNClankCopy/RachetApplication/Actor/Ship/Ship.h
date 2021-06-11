#ifndef RACHET_SHIP_H
#define RACHET_SHIP_H


#include "../../Actor.h"


namespace rachet {
class Ship : public rachet::Actor {
    using super = rachet::Actor;
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
#endif // !RACHET_SHIP_H