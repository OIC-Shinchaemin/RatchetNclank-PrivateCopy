#ifndef RATCHET_PLAYER_CROUCH_COMPONENT_H
#define RATCHET_PLAYER_CROUCH_COMPONENT_H


#include "PlayerActionComponent.h"

#include <functional>
#include <memory>
#include <string_view>
#include <vector>


namespace ratchet {
class PlayerCrouchComponent : public ratchet::PlayerActionComponent {
    using super = ratchet::PlayerActionComponent;
    using This = ratchet::PlayerCrouchComponent;
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
    struct Transition {
        std::string_view state;
        std::function<bool(void)> condition;
        Transition(std::string_view name, std::function<bool(void)> lambda) : 
            state(name), condition(lambda) {
        }
    };
    //! �J��
    //std::vector<Transition> _transition_pairs;
    //! ��]���x
    float _angular_speed;
    //! ���W�A��
    float _ideal_angle;
    //! ���͏��
    This::InputInfo _input_info;
    //! �J����
    std::weak_ptr<class PlayerMoveComponent> _move_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerCrouchComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerCrouchComponent(const PlayerCrouchComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerCrouchComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="speed"></param>
    void SetAngularSpeed(float speed);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="radian"></param>
    void SetIdealAngle(float radian);
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="move_speed"></param>
    /// <param name="angular_speed"></param>
    /// <param name="ideal_angle"></param>
    /// <returns>���s</returns>
    //bool Move(float move_speed, float angular_speed, float ideal_angle);
    /// <summary>
    /// �l��
    /// </summary>
    /// <param name="stick">�o��</param>
    /// <param name="move_angle">�o��</param>
    /// <returns></returns>
    //bool AquireInputData(Mof::CVector2& stick, float& move_angle);
};
}
#endif // !RATCHET_PLAYER_CROUCH_COMPONENT_H