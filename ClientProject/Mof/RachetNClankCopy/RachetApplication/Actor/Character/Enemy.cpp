#include "Enemy.h"

#include "../../Factory/FactoryManager.h"

#include "../../Component/Item/BoltActionStateComponent.h"
#include "../../Component/Item/BoltComponent.h"
#include "../../State/BoltActionStateDefine.h"


my::Enemy::Enemy() :
    super() {
    super::SetTag("Enemy");
}

my::Enemy::~Enemy() {
}

void my::Enemy::End(void) {
    auto param = my::Bolt::Param();
    for (int i = 0, n = ut::GenerateRandom(3, 3); i < n; i++) {
        param.transform.position = super::GetPosition();
        param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);

        float speed = 8.0f;
        float angle_y = ut::GenerateRandomF(0.0f, math::kTwoPi);
        Mof::CVector3 accele(0.0f, 0.0f, -speed);
        accele.RotationY(angle_y);

        param.speed.x = accele.x;
        param.speed.y = speed;
        param.speed.z = accele.z;

        param.angle.x = param.speed.x;
        param.angle.y = param.speed.y;
        param.angle.z = param.speed.z;

        auto bolt = my::FactoryManager::Singleton().CreateActor<my::Bolt>("../Resource/builder/bolt.json", &param);
        bolt->GetComponent<my::BoltActionStateComponent>()->ChangeState(state::BoltActionType::kMoved);
        Observable::Notify("AddRequest", bolt);
    } // for
    Observable::Notify("EnemyDead", shared_from_this());
    super::End();
}