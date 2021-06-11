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
    //! ���L����p�����[�^
    ratchet::actor::Actor::Param _param;
    //! �@�\
    std::vector<std::shared_ptr<ratchet::component::Component>> _components;
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    void SetActorParam(const ratchet::actor::Actor::Param& param);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const std::shared_ptr<ratchet::component::Component>& component);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void);
    /// <summary>
    /// �\�z
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
}
}
}
#endif // !RATCHET_FACTORY_BUILDER_ACTOR_ACTOR_BUILDER_H