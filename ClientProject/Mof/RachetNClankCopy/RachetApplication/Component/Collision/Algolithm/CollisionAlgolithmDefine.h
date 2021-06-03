#ifndef MY_COLLISION_ALGOLITHM_DEFINE_H
#define MY_COLLISION_ALGOLITHM_DEFINE_H


#include <string>


namespace my {
struct CollisionAlgolithmType {
    static std::string kPlayerEnemyCollisionAlgolithm;
    static std::string kPlayerEnemyMeleeAttackCollisionAlgolithm;
    static std::string kPlayerEnemyBulletCollisionAlgolithm;
    static std::string kPlayerShipCollisionAlgolithm;
    static std::string kPlayerWaterFlowCollisionAlgolithm;
    static std::string kEnemyPlayerCollisionAlgolithm;
    static std::string kEnemyOmniWrenchAttackCollisionAlgolithm;
    static std::string kSightPlayerCollisionAlgolithm;
    static std::string kSightEnemyCollisionAlgolithm;
    static std::string kEnemyEnemyCollisionAlgolithm;
    static std::string kEnemyMeleeAttackPlayerCollisionAlgolithm;
    static std::string kEnemyOmniWrenchCollisionAlgolithm;
    static std::string kEnemyBombGloveBulletCollisionAlgolithm;
    static std::string kEnemyPyrocitorBulletCollisionAlgolithm;
    static std::string kEnemyBlasterBulletCollisionAlgolithm;
    static std::string kEnemyBombGloveEffectCollisionAlgolithm;
    static std::string kBlasterBulletEnemyCollisionAlgolithm;
    static std::string kBombGloveBulletEnemyCollisionAlgolithm;
    static std::string kShipPlayerCollisionAlgolithm;
    static std::string kBoltPlayerCollisionAlgolithm;
    static std::string kPlayerShopCollisionAlgolithm;
};
}
#endif // !MY_COLLISION_ALGOLITHM_DEFINE_H