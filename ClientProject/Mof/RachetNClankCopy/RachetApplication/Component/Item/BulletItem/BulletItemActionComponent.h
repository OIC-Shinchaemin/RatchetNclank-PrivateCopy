#ifndef MY_BulletItem_ACTION_COMPONENT_H
#define MY_BulletItem_ACTION_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>

#include "../../VelocityComponent.h"
#include "BulletItemActionStateComponent.h"
#include "../../../State/BulletItemActionStateDefine.h"


namespace my {
class BulletItemActionComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! ���x
    std::weak_ptr<my::VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<my::BulletItemActionStateComponent> _state_com;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::VelocityComponent> GetVelocityComponent(void) const;
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
    BulletItemActionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BulletItemActionComponent(const BulletItemActionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BulletItemActionComponent();
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
#endif // !MY_BulletItem_ACTION_COMPONENT_H