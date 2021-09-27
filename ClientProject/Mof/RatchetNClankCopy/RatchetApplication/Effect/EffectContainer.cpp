#include "EffectContainer.h"
#include "EffectPool.h"
#include "EffectEmitter.h"


ratchet::effect::EffectContainer::EffectContainer():
    _resource(),
_effect_pair() {
    _effect_pair.emplace(effect::EffectType::BasicDamage, PoolAndEmitTarget());
    _effect_pair.at(effect::EffectType::BasicDamage).pool.SetResourcePath("../Resource/texture/effect/flash.png");

    _effect_pair.emplace(effect::EffectType::PlayerSense, PoolAndEmitTarget());
    _effect_pair.at(effect::EffectType::PlayerSense).pool.SetResourcePath("../Resource/texture/effect/sense.png");
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