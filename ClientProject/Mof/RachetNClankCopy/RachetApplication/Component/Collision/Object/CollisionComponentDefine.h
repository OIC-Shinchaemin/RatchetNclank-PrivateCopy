#ifndef MY_COLLISION_COMPONENT_DEFINE_H
#define MY_COLLISION_COMPONENT_DEFINE_H


#include <string>


namespace my {
struct CollisionComponentType {
    static std::string kPlayerCollisionComponent;
    static std::string kEnemyCollisionComponent;
    static std::string kEnemyAttackCollisionComponent;
    static std::string kSightCollisionComponent;
    static std::string kShipCollisionComponent;
    static std::string kBombGloveBulletCollisionComponent;
    static std::string kPyrocitorBulletCollisionComponent;
    static std::string kBlasterBulletCollisionComponent;
    static std::string kBombGloveEffectCollisionComponent;
};
}
#endif // !MY_COLLISION_COMPONENT_DEFINE_H