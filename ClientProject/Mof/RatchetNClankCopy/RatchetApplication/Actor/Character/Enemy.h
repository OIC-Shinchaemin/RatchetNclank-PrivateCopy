#ifndef RATCHET_ENEMY_H
#define RATCHET_ENEMY_H


#include "Character.h"

#include "../../Game/GameSystem/GameQuest.h"


namespace ratchet {
class Enemy : public ratchet::Character {
    using super = ratchet::Character;
public:
    enum class MotionType {
        IdleWait,
        MoveRun,
        AttackOne,
        Damage,
        CountMax,
    };
private:
    //! �ʒm�p
    base::core::Observable<const ratchet::GameQuest&> _quest_subject;
    /// <summary>
    /// ��ԕύX
    /// </summary>
    virtual void Activate(void) override;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Enemy();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    //virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Render(void) override;
};
}
#endif // !RATCHET_ENEMY_H