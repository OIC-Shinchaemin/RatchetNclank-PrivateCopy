#ifndef MY_ACTOR_BUILDER_H
#define MY_ACTOR_BUILDER_H


#include "IBuilder.h"

#include "../Actor.h"
#include "../Component/Component.h"


namespace my {
class ActorBuilder : public my::IBuilder {
    //! ���L����p�����[�^
    my::Actor::Param _param;
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    void SetActorParam(const my::Actor::Param& param);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const std::shared_ptr<my::Component>& component);
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
#endif // !MY_ACTOR_BUILDER_H