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
        //! プール
        ratchet::effect::EffectPool pool;
        //! エフェクト
        std::vector<effect::Effect*> effects;
    };
private:
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! ペアデータ
    std::unordered_map<effect::EffectType, PoolAndEmitTarget > _effect_pair;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EffectContainer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EffectContainer();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr) {
        this->_resource = ptr;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::effect::EffectEmitter> CreateEmitter(effect::EffectType type);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    bool Render(void);
};
}
#endif // !RATCHET_EFFECT_EFFECT_CONTAINER_H