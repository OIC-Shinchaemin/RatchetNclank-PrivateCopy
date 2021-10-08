#include "BombGloveBulletComponent.h"

#include "../Collision/Object/BombGloveBulletCollisionComponent.h"
#include "../../Actor/Bullet/BombGloveBullet.h"
#include "../../Actor/Effect/BombGloveEffect.h"
#include "../../Factory/FactoryManager.h"


bool ratchet::component::bullet::BombGloveBulletComponent::CollisionEnemy(const component::collision::CollisionInfo& in) {
    // expord start
    auto param = ratchet::actor::effect::ParticleEffect::Param();
    auto update_param = ratchet::actor::effect::ParticleEffect::UpdateParam();
    param.transform.position = super::GetOwner()->GetPosition();
    param.transform.scale = Mof::CVector3(0.2f, 0.2f, 0.2f);
    param.color = def::color_rgba::kRed;
    param.life_time = 0.7f;
    update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

    auto info = ratchet::actor::effect::ParticleEffect::Info();
    info.init_param = std::move(param);
    info.update_param = std::move(update_param);

    auto effect = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::effect::BombGloveEffect>("../Resource/builder/bomb_glove_effect.json", &param);
    effect->Start(std::move(info));
    super::GetOwner()->Notify("AddRequest", effect);

    // delete request
    super::GetOwner()->End();


    return true;
}

ratchet::component::bullet::BombGloveBulletComponent::BombGloveBulletComponent(int priority) :
    super(priority) {
}

ratchet::component::bullet::BombGloveBulletComponent::BombGloveBulletComponent(const BombGloveBulletComponent& obj) :
    super(obj) {
}

ratchet::component::bullet::BombGloveBulletComponent::~BombGloveBulletComponent() {
}

std::string ratchet::component::bullet::BombGloveBulletComponent::GetType(void) const {
    return "BombGloveBulletComponent";
}

bool ratchet::component::bullet::BombGloveBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::BombGloveBulletCollisionComponent>();

    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               "ScarecrowCollisionComponent",
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));


    return true;
}

bool ratchet::component::bullet::BombGloveBulletComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::bullet::BombGloveBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::bullet::BombGloveBulletComponent::Clone(void) {
    return std::make_shared<ratchet::component::bullet::BombGloveBulletComponent>(*this);
}