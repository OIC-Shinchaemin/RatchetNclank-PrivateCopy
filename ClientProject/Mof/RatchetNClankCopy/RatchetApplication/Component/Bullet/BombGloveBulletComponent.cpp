#include "BombGloveBulletComponent.h"

#include "../Collision/Object/BombGloveBulletCollisionComponent.h"
#include "../../Actor/Bullet/BombGloveBullet.h"
#include "../../Actor/Effect/BombGloveEffect.h"
#include "../../Factory/FactoryManager.h"


bool ratchet::BombGloveBulletComponent::CollisionEnemy(const ratchet::CollisionInfo& in) {
    // expord start
    auto param = ratchet::ParticleEffect::Param();
    auto update_param = ratchet::ParticleEffect::UpdateParam();
    param.transform.position = super::GetOwner()->GetPosition();
    param.transform.scale = Mof::CVector3(0.2f, 0.2f, 0.2f);
    param.color = def::color_rgba::kRed;
    param.life_time = 0.7f;
    update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

    auto info = ratchet::ParticleEffect::Info();
    info.init_param = std::move(param);
    info.update_param = std::move(update_param);

    auto effect = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::BombGloveEffect>("../Resource/builder/bomb_glove_effect.json", &param);
    effect->Start(std::move(info));
    super::GetOwner()->Notify("AddRequest", effect);

    // delete request
    super::GetOwner()->End();


    return true;
}

ratchet::BombGloveBulletComponent::BombGloveBulletComponent(int priority) :
    super(priority) {
}

ratchet::BombGloveBulletComponent::BombGloveBulletComponent(const BombGloveBulletComponent& obj) :
    super(obj) {
}

ratchet::BombGloveBulletComponent::~BombGloveBulletComponent() {
}

std::string ratchet::BombGloveBulletComponent::GetType(void) const {
    return "BombGloveBulletComponent";
}

bool ratchet::BombGloveBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::BombGloveBulletCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        // expord start
        auto param = ratchet::ParticleEffect::Param();
        auto update_param = ratchet::ParticleEffect::UpdateParam();
        param.transform.position = super::GetOwner()->GetPosition();
        param.transform.scale = Mof::CVector3(0.2f, 0.2f, 0.2f);
        param.color = def::color_rgba::kRed;
        param.life_time = 0.7f;
        update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

        auto info = ratchet::ParticleEffect::Info();
        info.init_param = std::move(param);
        info.update_param = std::move(update_param);
 
        auto effect = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::BombGloveEffect>("../Resource/builder/bomb_glove_effect.json", &param);
        effect->Start(std::move(info));
        super::GetOwner()->Notify("AddRequest", effect);

        // delete request
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool ratchet::BombGloveBulletComponent::Update(float delta_time) {
    return true;
}

bool ratchet::BombGloveBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BombGloveBulletComponent::Clone(void) {
    return std::make_shared<ratchet::BombGloveBulletComponent>(*this);
}