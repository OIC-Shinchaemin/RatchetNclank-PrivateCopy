#ifndef RACHET_ENEMY_H
#define RACHET_ENEMY_H


#include "Character.h"

#include "../../Game/GameSystem/GameQuest.h"


namespace rachet {
class Enemy : public rachet::Character {
    using super = rachet::Character;
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
    base::core::Observable<const rachet::GameQuest&> _quest_subject;
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
    base::core::Observable<const rachet::GameQuest&>* GetQuestSubject(void);
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
#endif // !RACHET_ENEMY_H