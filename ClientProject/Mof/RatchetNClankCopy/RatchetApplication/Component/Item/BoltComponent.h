#ifndef RATCHET_COMPONENT_ITEM_BOLT_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_BOLT_COMPONENT_H


#include "../UpdateComponent.h"

#include "../../Actor/Item/Bolt.h"


namespace ratchet::component::item {
class BoltComponent : public component::UpdateComponent {
    using super = component::UpdateComponent;
private:
    //! �A�N�^�[�p�����[�^
    actor::item::Bolt::Param _param;
    //! �ړ���
    std::weak_ptr<actor::Actor> _player;
    //! ���
    std::weak_ptr<class BoltActionStateComponent> _state_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BoltComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BoltComponent(const BoltComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BoltComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void SetActorParam(const actor::item::Bolt::Param& param);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const actor::item::Bolt::Param& GetActorParam(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<actor::Actor> GetPlayer(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_ITEM_BOLT_COMPONENT_H