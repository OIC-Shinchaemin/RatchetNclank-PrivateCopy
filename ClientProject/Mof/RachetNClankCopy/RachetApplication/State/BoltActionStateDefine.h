#ifndef STATE_BOLT_ACTION_STATE_DEFINE_H
#define STATE_BOLT_ACTION_STATE_DEFINE_H


#include <string>


namespace state {
struct BoltActionType {
    static std::string kDefault;
    static std::string kMoved;
    static std::string kGravitate;
};
}
#endif // !STATE_BOLT_ACTION_STATE_DEFINE_H