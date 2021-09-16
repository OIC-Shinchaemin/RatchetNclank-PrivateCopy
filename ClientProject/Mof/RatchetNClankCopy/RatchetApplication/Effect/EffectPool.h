#ifndef RATCHET_EFFECT_EFFECT_POOL_H
#define RATCHET_EFFECT_EFFECT_POOL_H


#include <array>

#include <Mof.h>

#include "Effect.h"


namespace ratchet::effect {
class EffectPool {
private:
    //! ���\�[�X�p�X
    std::string _effect_type_path;
    //! ���\�[�X�p�X
    static const int _effect_type_count = 10;
    //! �G�t�F�N�g
    std::array<effect::Effect, _effect_type_count > _effects;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EffectPool();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EffectPool();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string_view GetResourcePath(void) const;
    /// <summary>
    /// �擾
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    effect::Effect* Fetch(void);
};
}
#endif // !RATCHET_EFFECT_EFFECT_POOL_H