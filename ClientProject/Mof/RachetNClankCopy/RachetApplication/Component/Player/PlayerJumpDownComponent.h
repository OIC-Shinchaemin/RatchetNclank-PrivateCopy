#ifndef RACHET_PLAYER_JUMP_DOWN_COMPONENT_H
#define RACHET_PLAYER_JUMP_DOWN_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace rachet {
class PlayerJumpDownComponent : public rachet::PlayerActionComponent {
    using super = rachet::PlayerActionComponent;
    using This = rachet::PlayerJumpDownComponent;
    struct InputInfo {
        Mof::CVector2 in;
        float move_angle = 0.0f;
        bool move_flag = false;

        void Reset(void) {
            in.x = 0.0f;
            in.y = 0.0f;
            move_angle = 0.0f;
            move_flag = false;
        }
    };
private:
    //! �ő�
    float _jump_speed_max;
    //! ���x
    float _jump_speed;
    //! ����
    float _jump_decrase;
    //! ���͏��
    This::InputInfo _input_info;
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpDownComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpDownComponent(const PlayerJumpDownComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerJumpDownComponent();
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
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
};
}
#endif // !RACHET_PLAYER_JUMP_DOWN_COMPONENT_H