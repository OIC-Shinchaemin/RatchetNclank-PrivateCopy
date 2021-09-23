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
    //! 通知用
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&> _quest_subject;
    /// <summary>
    /// 状態変更
    /// </summary>
    virtual void Activate(void) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// アイテム
    /// </summary>
    /// <param name=""></param>
    void GenerateDropItem(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_ENEMY_H