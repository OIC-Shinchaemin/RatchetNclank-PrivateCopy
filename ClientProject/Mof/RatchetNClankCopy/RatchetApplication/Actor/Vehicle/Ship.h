#ifndef RATCHET_ACTOR_VEHICLE_SHIP_H
#define RATCHET_ACTOR_VEHICLE_SHIP_H


#include "../Actor.h"


namespace ratchet {
namespace actor {
namespace vehicle {
class Ship : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    enum class MotionType {
        Default,
        V4,
        CountMax,
    };
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Ship();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Ship();
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="builder"></param>
    virtual void Construct(const std::shared_ptr<ratchet::factory::builder::IBuilder>& builder) override;
};
}
}
}
#endif // !RATCHET_ACTOR_VEHICLE_SHIP_H