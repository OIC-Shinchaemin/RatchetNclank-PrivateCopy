#ifndef RATCHET_EFFECT_EFFECT_POOL_H
#define RATCHET_EFFECT_EFFECT_POOL_H


#include <array>

#include <Mof.h>

#include "Effect.h"


namespace ratchet::effect {
class EffectPool {
private:
    //! リソースパス
    std::string _effect_type_path;
    //! リソースパス
    static const int _effect_type_count = 10;
    //! エフェクト
    std::array<effect::Effect, _effect_type_count > _effects;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EffectPool();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EffectPool();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string_view GetResourcePath(void) const;
    /// <summary>
    /// 取得
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    effect::Effect* Fetch(void);
};
}
#endif // !RATCHET_EFFECT_EFFECT_POOL_H