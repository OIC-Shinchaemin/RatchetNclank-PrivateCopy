#ifndef MY_ACTION_COMPONENT_H
#define MY_ACTION_COMPONENT_H


#include "UpdateComponent.h"

#include <string_view>


namespace my {
class ActionComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    //void ChageState(const std::string& name);
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
};
}
#endif // !MY_ACTION_COMPONENT_H