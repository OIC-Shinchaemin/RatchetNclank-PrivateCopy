#ifndef RATCHET_EFFECT_EFFECT_CONTAINER_H
#define RATCHET_EFFECT_EFFECT_CONTAINER_H


#include <array>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "Effect.h"
#include "EffectPool.h"
#include "EffectEmitter.h"


namespace ratchet::effect {
class EffectEmitterHolder {
    using EmitterPtr = std::shared_ptr<ratchet::effect::EffectEmitter>;
private:
    //! �ۗL�G�~�b�^
    std::unordered_map<ratchet::effect::EffectType, EmitterPtr> _emitters;
public:
    bool Emplace(ratchet::effect::EffectType type, const EmitterPtr& elem) {
        auto it = _emitters.find(type);
        if (it != _emitters.end()) {
            return false;
        } // if
        
        _emitters.emplace(type, elem);
        return true;
    }
    EmitterPtr& At(ratchet::effect::EffectType type) {
        return this->_emitters.at(type);
    }
};
class EffectContainer {
    struct PoolAndEmitTarget {
        //! �v�[��
        ratchet::effect::EffectPool pool;
        //! �G�t�F�N�g
        std::vector<effect::Effect*> effects;

        PoolAndEmitTarget(const ratchet::effect::EffectPoolCreateInfo& pool_info) :
            pool(pool_info), effects() {
        }
    };
private:
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! �y�A�f�[�^
    std::unordered_map<effect::EffectType, PoolAndEmitTarget > _effect_pair;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    ratchet::effect::EffectPoolCreateInfo CreateEffectPoolCreateInfo(ratchet::effect::EffectType type) const;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EffectContainer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EffectContainer();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
        this->_resource = ptr;
    }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::effect::EffectEmitter> CreateEmitter(effect::EffectType type);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    bool Render(void);
};
}
#endif // !RATCHET_EFFECT_EFFECT_CONTAINER_H