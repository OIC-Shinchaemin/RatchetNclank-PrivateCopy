#ifndef RACHET_BOLT_DEFAULT_COMPONENT_H
#define RACHET_BOLT_DEFAULT_COMPONENT_H


#include "BoltActionComponent.h"

#include <memory>


namespace rachet {
class BoltDefaultComponent : public rachet::BoltActionComponent {
    using super = rachet::BoltActionComponent;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BoltDefaultComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BoltDefaultComponent(const BoltDefaultComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BoltDefaultComponent();
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
    virtual std::string_view GetStateType(void) const override;
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
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool End(void) override;
};
}
#endif // !RACHET_BOLT_DEFAULT_COMPONENT_H