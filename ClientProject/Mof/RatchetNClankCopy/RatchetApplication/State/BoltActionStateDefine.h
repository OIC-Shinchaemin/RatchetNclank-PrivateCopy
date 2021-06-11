#ifndef RATCHET_STATE_BOLT_ACTION_STATE_DEFINE_H
#define RATCHET_STATE_BOLT_ACTION_STATE_DEFINE_H


#include <string>


namespace ratchet {
namespace state {
struct BoltActionType {
    static std::string kDefault;
    static std::string kMoved;
    static std::string kGravitate;
};
}
}
#endif // !RATCHET_STATE_BOLT_ACTION_STATE_DEFINE_H