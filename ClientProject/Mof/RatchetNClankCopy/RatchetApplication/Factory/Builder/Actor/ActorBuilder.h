#ifndef RATCHET_FACTORY_BUILDER_ACTOR_ACTOR_BUILDER_H
#define RATCHET_FACTORY_BUILDER_ACTOR_ACTOR_BUILDER_H


#include "../IBuilder.h"

#include "../../../Actor/Actor.h"
#include "../../../Component/Component.h"


namespace ratchet {
namespace factory {
namespace builder {
namespace actor {
class ActorBuilder : public ratchet::factory::builder::IBuilder {
    //! 所有するパラメータ
    ratchet::actor::Actor::Param _param;
    //! 機能
    std::vector<std::shared_ptr<ratchet::component::Component>> _components;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ActorBuilder();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ActorBuilder();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    void SetActorParam(const ratchet::actor::Actor::Param& param);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const std::shared_ptr<ratchet::component::Component>& component);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void);
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
#endif // !RATCHET_FACTORY_BUILDER_ACTOR_ACTOR_BUILDER_H