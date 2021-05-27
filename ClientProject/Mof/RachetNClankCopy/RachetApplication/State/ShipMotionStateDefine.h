#ifndef STATE_SHIP_MOTION_STATE_DEFINE_H
#define STATE_SHIP_MOTION_STATE_DEFINE_H


#include <string>


namespace state {
struct ShipMotionStateType {
    static std::string kShipMotionIdleState;
    static std::string kShipMotionLandingState;
    static std::string kShipMotionTakeoffState;
};
}
#endif // !STATE_SHIP_MOTION_STATE_DEFINE_H