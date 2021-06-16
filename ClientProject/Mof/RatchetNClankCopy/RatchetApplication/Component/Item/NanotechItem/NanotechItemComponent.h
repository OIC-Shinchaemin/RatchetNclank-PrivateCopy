#ifndef RATCHET_COMPONENT_ITEM_NANOTECH_ITEM_NanotechItem_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_NANOTECH_ITEM_NanotechItem_COMPONENT_H


#include "../../UpdateComponent.h"

#include "../../../Actor/Item/NanotechItem.h"


namespace ratchet { namespace component { namespace item { namespace nanotechitem {
class NanotechItemComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! �A�N�^�[�p�����[�^
    ratchet::actor::item::NanotechItem::Param _param;
    //! �ړ���
    std::weak_ptr<ratchet::actor::Actor> _player;
    //! ���
    std::weak_ptr<class NanotechItemActionStateComponent> _state_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    NanotechItemComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    NanotechItemComponent(const NanotechItemComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NanotechItemComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void SetActorParam(const ratchet::actor::item::NanotechItem::Param& param);
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
    const ratchet::actor::item::NanotechItem::Param& GetActorParam(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::Actor> GetPlayer(void) const;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};}}}
}
#endif // !RATCHET_COMPONENT_ITEM_NANOTECH_ITEM_NanotechItem_COMPONENT_H