#ifndef MY_PLAYER_H
#define MY_PLAYER_H


#include "Character.h"
#include "My/Core/Observer.h"

#include "../Weapon/OmniWrench.h"
#include "../Weapon/Mechanical.h"
#include "../../Game/GameSystem/QuickChangeSystem.h"
#include "../../Component/Player/PlayerComponent.h"


namespace my {
class Player : public my::Character, 
    public my::Observer<std::shared_ptr<my::Mechanical>>, 
    public my::Observer<const my::QuickChangeSystem::Info&> {
    using super = my::Character;
public:
    enum class MotionType {
        IdleWait,
        MoveRun,
        JumpSet,
        JumpUp,
        JumpDown,
        JumpLanding,
        DoubleJump,
        MeleeAttackOne,
        MeleeAttackOneEnd,
        MeleeAttackTwo,
        MeleeAttackTwoEnd,
        MeleeAttackThree,
        MeleeAttackThreeEnd,
        DamageA,
        DamageDead,
        CountMax,
    };
private:
    //! ����
    std::weak_ptr<my::Mechanical>_current_mechanical;
    //! ����
    //std::shared_ptr<my::OmniWrench> _omniwrench;
    //! �q�A�N�^�[
    std::vector<std::shared_ptr<my::Actor>> _children;
    //! �v���C���[
    std::weak_ptr<my::PlayerComponent> _player_com;
    //! �L��
    bool _enable;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Player();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Player();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(std::shared_ptr<my::Mechanical> change) override;
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const my::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="tag"></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor> GetChild(const std::string& tag) const;
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Disable(void);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddChild(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_PLAYER_H