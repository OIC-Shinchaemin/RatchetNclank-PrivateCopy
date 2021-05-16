#ifndef MY_ACTION_COMPONENT_H
#define MY_ACTION_COMPONENT_H


#include "UpdateComponent.h"

#include <string_view>


namespace my {
class ActionComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ActionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ActionComponent(const ActionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActionComponent();
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
    virtual std::string_view GetStateType(void) const;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void);
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool End(void);
};
}
#endif // !MY_ACTION_COMPONENT_H