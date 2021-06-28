#ifndef RATCHET_FACTORY_BUILDER_ACTOR_OMNI_WRENCH_BUILDER_H
#define RATCHET_FACTORY_BUILDER_ACTOR_OMNI_WRENCH_BUILDER_H


#include "ActorBuilder.h"

#include "../../../Actor/Weapon/OmniWrench.h"


namespace ratchet {
namespace factory {
namespace builder {
namespace actor {
class OmniWrenchBuilder : public ratchet::factory::builder::actor::ActorBuilder {
    using super = ratchet::factory::builder::actor::ActorBuilder;
private:
    //! リソース
    //std::weak_ptr<ratchet::ResourceMgr> _resource;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    OmniWrenchBuilder();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~OmniWrenchBuilder();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    //void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void) override;
    /// <summary>
    /// 構築
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
}
}
}
#endif // !RATCHET_FACTORY_BUILDER_ACTOR_OMNI_WRENCH_BUILDER_H