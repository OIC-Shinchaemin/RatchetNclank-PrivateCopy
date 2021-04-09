#ifndef MY_ACTOR_BUILDER_H
#define MY_ACTOR_BUILDER_H


#include "IBuilder.h"

#include "../Actor.h"
#include "../Component/Component.h"


namespace my {
class ActorBuilder : public my::IBuilder {
    //! �@�\
    std::vector<std::shared_ptr<my::Component>> _components;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ActorBuilder();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActorBuilder();
    /// <summary>
    /// �\�z
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
#endif // !MY_ACTOR_BUILDER_H