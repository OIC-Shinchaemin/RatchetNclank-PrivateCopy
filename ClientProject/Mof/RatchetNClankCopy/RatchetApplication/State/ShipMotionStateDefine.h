#ifndef RATCHET_STATE_SHIP_MOTION_STATE_DEFINE_H
#define RATCHET_STATE_SHIP_MOTION_STATE_DEFINE_H


#include <string>

namespace ratchet::state {
struct ShipMotionStateType {
    static std::string kShipMotionIdleState;
    static std::string kShipMotionLandingState;
    static std::string kShipMotionTakeoffState;
};
}
#endif // !RATCHET_STATE_SHIP_MOTION_STATE_DEFINE_H