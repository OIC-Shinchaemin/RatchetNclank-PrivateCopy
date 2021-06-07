#ifndef STATE_BULLET_ITEM_ACTION_STATE_DEFINE_H
#define STATE_BULLET_ITEM_ACTION_STATE_DEFINE_H


#include <string>


namespace state {
struct BulletItemActionType {
    static std::string kDefault;
    static std::string kMoved;
    static std::string kGravitate;
};
}
#endif // !STATE_BULLET_ITEM_ACTION_STATE_DEFINE_H