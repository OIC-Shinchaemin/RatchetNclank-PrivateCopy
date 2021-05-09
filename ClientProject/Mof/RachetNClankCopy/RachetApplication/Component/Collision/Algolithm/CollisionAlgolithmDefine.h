#ifndef MY_COLLISION_ALGOLITHM_DEFINE_H
#define MY_COLLISION_ALGOLITHM_DEFINE_H


#include <string>


namespace my {
struct CollisionAlgolithmType {
    static std::string kPlayerEnemyCollisionAlgolithm;
    static std::string kPlayerEnemyAttackCollisionAlgolithm;
    static std::string kPlayerEnemyBulletCollisionAlgolithm;
    static std::string kPlayerShipCollisionAlgolithm;
    static std::string kPlayerWaterFlowCollisionAlgolithm;
    static std::string kEnemyPlayerCollisionAlgolithm;
    static std::string kEnemyPlayerMeleeAttackCollisionAlgolithm;
    static std::string kSightPlayerCollisionAlgolithm;
    static std::string kSightEnemyCollisionAlgolithm;
    static std::string kEnemyEnemyCollisionAlgolithm;
    static std::string kEnemyAttackPlayerCollisionAlgolithm;
    static std::string kEnemyBombGloveBulletCollisionAlgolithm;
    static std::string kEnemyPyrocitorBulletCollisionAlgolithm;
    static std::string kEnemyBlasterBulletCollisionAlgolithm;
    static std::string kEnemyBombGloveEffectCollisionAlgolithm;
    static std::string kBlasterBulletEnemyCollisionAlgolithm;
    static std::string kBombGloveBulletEnemyCollisionAlgolithm;
};
}
#endif // !MY_COLLISION_ALGOLITHM_DEFINE_H