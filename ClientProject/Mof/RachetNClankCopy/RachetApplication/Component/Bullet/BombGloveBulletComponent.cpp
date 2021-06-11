#include "BombGloveBulletComponent.h"

#include "../Collision/Object/BombGloveBulletCollisionComponent.h"
#include "../../Actor/Bullet/BombGloveBullet.h"
#include "../../Actor/Effect/BombGloveEffect.h"
#include "../../Factory/FactoryManager.h"


bool rachet::BombGloveBulletComponent::CollisionEnemy(const rachet::CollisionInfo& in) {
    // expord start
    auto param = rachet::ParticleEffect::Param();
    auto update_param = rachet::ParticleEffect::UpdateParam();
    param.transform.position = super::GetOwner()->GetPosition();
    param.transform.scale = Mof::CVector3(0.2f, 0.2f, 0.2f);
    param.color = def::color_rgba::kRed;
    param.life_time = 0.7f;
    update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

    auto info = rachet::ParticleEffect::Info();
    info.init_param = std::move(param);
    info.update_param = std::move(update_param);

    auto effect = rachet::FactoryManager::Singleton().CreateActor<rachet::BombGloveEffect>("../Resource/builder/bomb_glove_effect.json", &param);
    effect->Start(std::move(info));
    super::GetOwner()->Notify("AddRequest", effect);

    // delete request
    super::GetOwner()->End();


    return true;
}

rachet::BombGloveBulletComponent::BombGloveBulletComponent(int priority) :
    super(priority) {
}

rachet::BombGloveBulletComponent::BombGloveBulletComponent(const BombGloveBulletComponent& obj) :
    super(obj) {
}

rachet::BombGloveBulletComponent::~BombGloveBulletComponent() {
}

std::string rachet::BombGloveBulletComponent::GetType(void) const {
    return "BombGloveBulletComponent";
}

bool rachet::BombGloveBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<rachet::BombGloveBulletCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        // expord start
        auto param = rachet::ParticleEffect::Param();
        auto update_param = rachet::ParticleEffect::UpdateParam();
        param.transform.position = super::GetOwner()->GetPosition();
        param.transform.scale = Mof::CVector3(0.2f, 0.2f, 0.2f);
        param.color = def::color_rgba::kRed;
        param.life_time = 0.7f;
        update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

        auto info = rachet::ParticleEffect::Info();
        info.init_param = std::move(param);
        info.update_param = std::move(update_param);
 
        auto effect = rachet::FactoryManager::Singleton().CreateActor<rachet::BombGloveEffect>("../Resource/builder/bomb_glove_effect.json", &param);
        effect->Start(std::move(info));
        super::GetOwner()->Notify("AddRequest", effect);

        // delete request
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool rachet::BombGloveBulletComponent::Update(float delta_time) {
    return true;
}

bool rachet::BombGloveBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BombGloveBulletComponent::Clone(void) {
    return std::make_shared<rachet::BombGloveBulletComponent>(*this);
}