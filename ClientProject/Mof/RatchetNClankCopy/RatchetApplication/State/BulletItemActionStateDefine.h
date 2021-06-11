#ifndef RATCHET_STATE_BULLET_ITEM_ACTION_STATE_DEFINE_H
#define RATCHET_STATE_BULLET_ITEM_ACTION_STATE_DEFINE_H


#include <string>


namespace ratchet {
namespace state {
struct BulletItemActionType {
    static std::string kDefault;
    static std::string kMoved;
    static std::string kGravitate;
};
}
}
#endif // !RATCHET_STATE_BULLET_ITEM_ACTION_STATE_DEFINE_H