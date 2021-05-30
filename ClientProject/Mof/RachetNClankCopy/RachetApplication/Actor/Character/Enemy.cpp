#include "Enemy.h"

#include "../../Factory/FactoryManager.h"


my::Enemy::Enemy() :
    super() {
    super::SetTag("Enemy");
}

my::Enemy::~Enemy() {
}

void my::Enemy::End(void) {
    auto param = my::Actor::Param();
    //param.transform.position = super::GetPosition();
    param.transform.position = super::GetPosition();
    param.transform.position.y += 4.0f;
    param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
    auto bolt = my::FactoryManager::Singleton().CreateActor<my::Actor>("../Resource/builder/bolt.json", &param);
    Observable::Notify("AddRequest", bolt);

    Observable::Notify("EnemyDead", shared_from_this());
    super::End();
}