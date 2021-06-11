#ifndef RACHET_NanotechItem_ACTION_STATE_COMPONENT_H
#define RACHET_NanotechItem_ACTION_STATE_COMPONENT_H


#include "../../ActionStateComponent.h"

#include "../../../State/NanotechItemActionStateDefine.h"


namespace rachet {
class NanotechItemActionStateComponent : public rachet::ActionStateComponent {
    using super = rachet::ActionStateComponent;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    NanotechItemActionStateComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    NanotechItemActionStateComponent(const NanotechItemActionStateComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NanotechItemActionStateComponent();
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool CanTransition(const std::string& next);
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !RACHET_NanotechItem_ACTION_STATE_COMPONENT_H