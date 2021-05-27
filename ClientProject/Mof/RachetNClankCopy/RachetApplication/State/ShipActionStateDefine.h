#ifndef STATE_SHIP_ACTION_STATE_DEFINE_H
#define STATE_SHIP_ACTION_STATE_DEFINE_H


#include <string>


namespace state {
struct ShipActionStateType {
    static std::string kShipActionIdleState;
    static std::string kShipActionLandingState;
    static std::string kShipActionTakeoffState;
};
}
#endif // !STATE_SHIP_ACTION_STATE_DEFINE_H