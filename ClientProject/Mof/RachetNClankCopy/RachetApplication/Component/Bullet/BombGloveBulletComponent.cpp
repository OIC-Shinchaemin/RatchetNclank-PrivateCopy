#include "BombGloveBulletComponent.h"

#include "../Collision/Object/BombGloveBulletCollisionComponent.h"
#include "../../Actor/Bullet/BombGloveBullet.h"
#include "../../Actor/Effect/BombGloveEffect.h"
#include "../../Factory/FactoryManager.h"


bool my::BombGloveBulletComponent::CollisionEnemy(const my::CollisionInfo& in) {
    // expord start
    auto param = my::ParticleEffect::Param();
    auto update_param = my::ParticleEffect::UpdateParam();
    param.transform.position = super::GetOwner()->GetPosition();
    param.transform.scale = Mof::CVector3(0.2f, 0.2f, 0.2f);
    param.color = def::color_rgba::kRed;
    param.life_time = 0.7f;
    update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

    auto info = my::ParticleEffect::Info();
    info.init_param = std::move(param);
    info.update_param = std::move(update_param);

    auto effect = my::FactoryManager::Singleton().CreateActor<my::BombGloveEffect>("../Resource/builder/bomb_glove_effect.json", &param);
    effect->Start(std::move(info));
    super::GetOwner()->Notify("AddRequest", effect);

    // delete request
    super::GetOwner()->End();


    return true;
}

my::BombGloveBulletComponent::BombGloveBulletComponent(int priority) :
    super(priority) {
}

my::BombGloveBulletComponent::BombGloveBulletComponent(const BombGloveBulletComponent& obj) :
    super(obj) {
}

my::BombGloveBulletComponent::~BombGloveBulletComponent() {
}

std::string my::BombGloveBulletComponent::GetType(void) const {
    return "BombGloveBulletComponent";
}

bool my::BombGloveBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<my::BombGloveBulletCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        // expord start
        auto param = my::ParticleEffect::Param();
        auto update_param = my::ParticleEffect::UpdateParam();
        param.transform.position = super::GetOwner()->GetPosition();
        param.transform.scale = Mof::CVector3(0.2f, 0.2f, 0.2f);
        param.color = def::color_rgba::kRed;
        param.life_time = 0.7f;
        update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

        auto info = my::ParticleEffect::Info();
        info.init_param = std::move(param);
        info.update_param = std::move(update_param);
 
        auto effect = my::FactoryManager::Singleton().CreateActor<my::BombGloveEffect>("../Resource/builder/bomb_glove_effect.json", &param);
        effect->Start(std::move(info));
        super::GetOwner()->Notify("AddRequest", effect);

        // delete request
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool my::BombGloveBulletComponent::Update(float delta_time) {
    return true;
}

bool my::BombGloveBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BombGloveBulletComponent::Clone(void) {
    return std::make_shared<my::BombGloveBulletComponent>(*this);
}