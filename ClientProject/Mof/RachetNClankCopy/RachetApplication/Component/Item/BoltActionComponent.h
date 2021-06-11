#ifndef RACHET_BOLT_ACTION_COMPONENT_H
#define RACHET_BOLT_ACTION_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "../VelocityComponent.h"
#include "BoltActionStateComponent.h"
#include "../../State/BoltActionStateDefine.h"


namespace rachet {
class BoltActionComponent : public rachet::ActionComponent {
    using super = rachet::ActionComponent;
private:
    //! ���x
    std::weak_ptr<rachet::VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<rachet::BoltActionStateComponent> _state_com;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<rachet::VelocityComponent> GetVelocityComponent(void) const;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    bool ChangeActionState(const std::string& name);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BoltActionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BoltActionComponent(const BoltActionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BoltActionComponent();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RACHET_BOLT_ACTION_COMPONENT_H