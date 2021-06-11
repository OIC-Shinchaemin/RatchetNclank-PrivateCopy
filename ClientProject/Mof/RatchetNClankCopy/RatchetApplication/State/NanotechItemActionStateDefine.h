#ifndef STATE_NANOTECH_ITEM_ACTION_STATE_DEFINE_H
#define STATE_NANOTECH_ITEM_ACTION_STATE_DEFINE_H


#include <string>


namespace state {
struct NanotechItemActionType {
    static std::string kDefault;
    static std::string kMoved;
    static std::string kGravitate;
};
}
#endif // !STATE_NANOTECH_ITEM_ACTION_STATE_DEFINE_H