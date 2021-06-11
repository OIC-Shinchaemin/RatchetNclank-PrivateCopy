#ifndef RACHET_NanotechItem_COMPONENT_H
#define RACHET_NanotechItem_COMPONENT_H


#include "../../UpdateComponent.h"

#include "../../../Actor/Item/NanotechItem.h"


namespace rachet {
class NanotechItemComponent : public rachet::UpdateComponent {
    using super = rachet::UpdateComponent;
private:
    //! �A�N�^�[�p�����[�^
    rachet::NanotechItem::Param _param;
    //! �ړ���
    std::weak_ptr<rachet::Actor> _player;
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
    void SetActorParam(const rachet::NanotechItem::Param& param);
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
    const rachet::NanotechItem::Param& GetActorParam(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Actor> GetPlayer(void) const;
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
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
};
}
#endif // !RACHET_NanotechItem_COMPONENT_H