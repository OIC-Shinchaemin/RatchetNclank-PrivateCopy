#ifndef RATCHET_ACTOR_CHARACTER_ENEMY_H
#define RATCHET_ACTOR_CHARACTER_ENEMY_H


#include "Character.h"

#include "../../Game/GameSystem/GameQuest.h"


namespace ratchet::actor::character {
class Enemy : public ratchet::actor::character::Character {
    using super = ratchet::actor::character::Character;
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
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&> _quest_subject;
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
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// �A�C�e��
    /// </summary>
    /// <param name=""></param>
    void GenerateDropItem(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_ENEMY_H