#include "EffectContainer.h"
#include "EffectPool.h"
#include "EffectEmitter.h"


ratchet::effect::EffectPoolCreateInfo ratchet::effect::EffectContainer::CreateEffectPoolCreateInfo(ratchet::effect::EffectType type) const {
    auto pool_create_info = ratchet::effect::EffectPoolCreateInfo();
    switch (type) {
        case ratchet::effect::EffectType::BasicDamage:
            pool_create_info.pool_count = 10;
            pool_create_info.path = "../Resource/texture/effect/flash.png";
            break;
        case ratchet::effect::EffectType::PlayerSense:
            pool_create_info.pool_count = 10;
            pool_create_info.path = "../Resource/texture/effect/sense.png";
            break;
        case ratchet::effect::EffectType::PopStar:
            pool_create_info.pool_count = 10;
            pool_create_info.path = "../Resource/texture/effect/star.png";
            break;
        case ratchet::effect::EffectType::EnemyBulletEnd:
            pool_create_info.pool_count = 20;
            pool_create_info.path = "../Resource/texture/effect/enemy_bullet_end_effect.png";
            break;
        default:
            break;
    } // switch
    return pool_create_info;
}

ratchet::effect::EffectContainer::EffectContainer() :
    _resource(),
    _effect_pair() {
    using Type = effect::EffectType;
    _effect_pair.emplace(Type::BasicDamage, PoolAndEmitTarget(this->CreateEffectPoolCreateInfo(Type::BasicDamage)));
    _effect_pair.emplace(Type::PlayerSense, PoolAndEmitTarget(this->CreateEffectPoolCreateInfo(Type::PlayerSense)));
    _effect_pair.emplace(Type::PopStar, PoolAndEmitTarget(this->CreateEffectPoolCreateInfo(Type::PopStar)));
    _effect_pair.emplace(Type::EnemyBulletEnd, PoolAndEmitTarget(this->CreateEffectPoolCreateInfo(Type::EnemyBulletEnd)));
}

ratchet::effect::EffectContainer::~EffectContainer() {
}

std::shared_ptr<ratchet::effect::EffectEmitter> ratchet::effect::EffectContainer::CreateEmitter(effect::EffectType type) {
    auto re = std::make_shared<ratchet::effect::EffectEmitter>();
    auto& pair = _effect_pair.at(type);

    re->SetPool(&pair.pool);
    re->SetOutputTarget(&pair.effects);
    return re;
}

bool ratchet::effect::EffectContainer::Update(float delta_time) {
    for (auto& pair : _effect_pair) {
        ut::EraseRemove(pair.second.effects, [](auto effect) {
            return !effect->IsEnable();
        });
    } // for

    for (auto& pair : _effect_pair) {
        for (auto& effect : pair.second.effects) {
            effect->Update(delta_time);
        } // for
    } // for
    return true;
}

bool ratchet::effect::EffectContainer::Render(void) {
    for (auto& pair : _effect_pair) {
        for (auto& effect : pair.second.effects) {
            if (!effect->IsEnable()) {
                continue;
            } // if


            if (auto resource = _resource.lock()) {
                auto path = pair.second.pool.GetResourcePath();
                auto tex = resource->Get<std::shared_ptr<Mof::CTexture>>(path.data());
                auto& param = effect->GetBasicParam();
                if (tex) {
                    Mof::CMatrix44 scale, rotate, translate;
                    //Mof::CQuaternion quat; quat.Rotation(param.transform.rotate);
                    Mof::CQuaternion quat; quat.Rotation(Mof::CVector3());

                    scale.Scaling(param.transform.scale, scale);
                    quat.ConvertMatrixTranspose(rotate);
                    translate.Translation(param.transform.position, translate);

                    Mof::CMatrix44 world = scale * rotate * translate;
                    auto camera = ::CGraphicsUtilities::GetCamera();
                    tex->Render(camera->GetBillBoardMatrix() * world, param.color.ToU32Color());
                } // if

            } // if

        } // for
    } // for
    return true;
}