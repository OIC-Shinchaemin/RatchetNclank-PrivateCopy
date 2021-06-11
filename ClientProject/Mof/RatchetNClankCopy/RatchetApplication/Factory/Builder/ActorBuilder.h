#ifndef RATCHET_ACTOR_BUILDER_H
#define RATCHET_ACTOR_BUILDER_H


#include "IBuilder.h"

#include "../../Actor.h"
#include "../../Component/Component.h"


namespace ratchet {
class ActorBuilder : public ratchet::IBuilder {
    //! 所有するパラメータ
    ratchet::Actor::Param _param;
    //! 機能
    std::vector<std::shared_ptr<ratchet::Component>> _components;
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
    void SetActorParam(const ratchet::Actor::Param& param);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const std::shared_ptr<ratchet::Component>& component);
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
#endif // !RATCHET_ACTOR_BUILDER_H