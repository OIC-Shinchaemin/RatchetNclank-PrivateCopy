#ifndef MY_COLLISION_COMPONENT_DEFINE_H
#define MY_COLLISION_COMPONENT_DEFINE_H


#include <string>


namespace my {
struct CollisionComponentType {
    static std::string kPlayerCollisionComponent;
    static std::string kPlayerMeleeAttackCollisionComponent;
    static std::string kEnemyCollisionComponent;
    static std::string kEnemyMeleeAttackCollisionComponent;
    static std::string kEnemyBulletCollisionComponent;
    static std::string kSightCollisionComponent;
    static std::string kShipCollisionComponent;
    static std::string kBoltCollisionComponent;
    static std::string kBulletItemCollisionComponent;
    static std::string kNanotechItemCollisionComponent;
    static std::string kOmniWrenchCollisionComponent;
    static std::string kBombGloveBulletCollisionComponent;
    static std::string kPyrocitorBulletCollisionComponent;
    static std::string kBlasterBulletCollisionComponent;
    static std::string kBombGloveEffectCollisionComponent;
    static std::string kWaterFlowCollisionComponent;
    static std::string kCameraCollisionComponent;
    static std::string kShopCollisionComponent;
};
}
#endif // !MY_COLLISION_COMPONENT_DEFINE_H