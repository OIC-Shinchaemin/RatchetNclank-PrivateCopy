#ifndef RATCHET_SHIP_H
#define RATCHET_SHIP_H


#include "../../Actor.h"


namespace ratchet {
class Ship : public ratchet::Actor {
    using super = ratchet::Actor;
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
    virtual void Construct(const std::shared_ptr<ratchet::factory::builder::IBuilder>& builder) override;
};
}
#endif // !RATCHET_SHIP_H