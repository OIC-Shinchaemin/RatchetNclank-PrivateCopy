#ifndef MY_PLAYER_COMPONENT_H
#define MY_PLAYER_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace my {
class PlayerComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! �ҋ@
    std::weak_ptr<class PlayerIdleComponent> _idle_com;
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;

    bool MoveByKeyboard(float angular_speed, float speed);
    void MoveByGamepad(float angular_speed, float speed);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerComponent(const PlayerComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerComponent();
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
};
}
#endif // !MY_PLAYER_COMPONENT_H