#ifndef RATCHET_EFFECT_EFFECT_CONTAINER_H
#define RATCHET_EFFECT_EFFECT_CONTAINER_H


#include <array>

#include <Mof.h>

#include "Effect.h"
#include "EffectPool.h"
#include "EffectEmitter.h"


namespace ratchet::effect {
class EffectContainer {
    struct PoolAndEmitTarget {
        //! �v�[��
        ratchet::effect::EffectPool pool;
        //! �G�t�F�N�g
        std::vector<effect::Effect*> effects;
    };
private:
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! �y�A�f�[�^
    std::unordered_map<effect::EffectType, PoolAndEmitTarget > _effect_pair;
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