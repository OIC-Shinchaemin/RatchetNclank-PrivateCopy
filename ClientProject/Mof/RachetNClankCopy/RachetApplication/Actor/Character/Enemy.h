#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"

#include "../../Game/GameSystem/GameQuest.h"


namespace my {
class Enemy : public my::Character {
    using super = my::Character;
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
    my::Observable<const my::GameQuest&> _quest_subject;
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
    my::Observable<const my::GameQuest&>* GetQuestSubject(void);
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
#endif // !MY_ENEMY_H