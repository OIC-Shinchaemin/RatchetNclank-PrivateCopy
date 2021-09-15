#ifndef RATCHET_STATE_SHIP_ACTION_STATE_DEFINE_H
#define RATCHET_STATE_SHIP_ACTION_STATE_DEFINE_H


#include <string>


namespace ratchet::state {
struct ShipActionStateType {
    static std::string kShipActionIdleState;
    static std::string kShipActionLandingState;
    static std::string kShipActionTakeoffState;
};
}
#endif // !RATCHET_STATE_SHIP_ACTION_STATE_DEFINE_H