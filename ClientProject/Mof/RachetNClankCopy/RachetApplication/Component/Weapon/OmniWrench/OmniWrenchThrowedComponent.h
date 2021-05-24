#ifndef MY_OMNI_WRENCH_THROWED_COMPONENT_H
#define MY_OMNI_WRENCH_THROWED_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>


namespace my {
class OmniWrenchThrowedComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! �J��
    Mof::CVector3 _local_translate;
    //! ����
    float _move_speed;
    //! �ړ���������
    float _moved_distance;
    //! 臒l
    float _moved_distance_threshold;
    //! �i�s����
    Mof::CVector3 _ideal_move_direction;
    //! ���L��
    std::weak_ptr<my::Actor> _weapon_owner;
    //! ���x
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<class OmniWrenchActionStateComponent> _action_state_com;
    //! �Փ�
    std::weak_ptr<class OmniWrenchCollisionComponent> _collision_com;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChageState(const std::string& name);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    OmniWrenchThrowedComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    OmniWrenchThrowedComponent(const OmniWrenchThrowedComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~OmniWrenchThrowedComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetWeaponOwner(const std::shared_ptr<my::Actor>& ptr);
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
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
#endif // !MY_OMNI_WRENCH_THROWED_COMPONENT_H