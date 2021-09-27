#ifndef RATCHET_EFFECT_EFFECT_POOL_H
#define RATCHET_EFFECT_EFFECT_POOL_H


#include <array>

#include <Mof.h>

#include "Effect.h"


namespace ratchet::effect {
struct EffectPoolCreateInfo {
    //! ���\�[�X�p�X
    std::string path;
    //! �m�ې�
    int pool_count = 10;
};

template<typename T>
class ImmutableArray {
private:
    std::vector<T> _elements;
public:
    ImmutableArray(int size) {
        _elements.resize(size);
    }
    auto& at(int index) {
        return this->_elements.at(index);
    }
    auto size(void) {
        return this->_elements.size();
    }
    auto begin(void) noexcept {
        return this->_elements.begin();
    }
    auto end(void) noexcept {
        return this->_elements.end();
    }
};
class EffectPool {
private:
    //! ���\�[�X�p�X
    std::string _effect_type_path;
    //! ���\�[�X�p�X
    static const int _effect_type_count = 10;
    //! �G�t�F�N�g
    ratchet::effect::ImmutableArray<effect::Effect> _effects;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EffectPool(const ratchet::effect::EffectPoolCreateInfo& info);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EffectPool();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="path"></param>
    void SetResourcePath(const std::string& path);
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