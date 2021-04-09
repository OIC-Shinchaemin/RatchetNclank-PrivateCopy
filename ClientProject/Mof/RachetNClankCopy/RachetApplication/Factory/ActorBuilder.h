#ifndef MY_ACTOR_BUILDER_H
#define MY_ACTOR_BUILDER_H


#include "IBuilder.h"

#include "../Actor.h"
#include "../Component/Component.h"


namespace my {
class ActorBuilder : public my::IBuilder {
    //! 機能
    std::vector<std::shared_ptr<my::Component>> _components;
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
    /// 構築
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
#endif // !MY_ACTOR_BUILDER_H