#ifndef RATCHET_STATE_OMNI_WRENCH_ACTION_STATE_DEFINE_H
#define RATCHET_STATE_OMNI_WRENCH_ACTION_STATE_DEFINE_H


#include <string>


namespace ratchet::state {
struct OmniWrenchActionStateType {
    static std::string kOmniWrenchActionDefaultState;
    static std::string kOmniWrenchActionThrowedState;
};
}
#endif // !RATCHET_STATE_OMNI_WRENCH_ACTION_STATE_DEFINE_H