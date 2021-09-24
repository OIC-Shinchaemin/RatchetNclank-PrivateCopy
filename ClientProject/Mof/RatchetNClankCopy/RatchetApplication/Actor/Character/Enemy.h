#ifndef RATCHET_ACTOR_CHARACTER_ENEMY_H
#define RATCHET_ACTOR_CHARACTER_ENEMY_H


#include "Character.h"

#include "../../Game/GameSystem/GameQuest.h"
#include "../../Effect/EffectEmitter.h"
#include "../../Effect/EffectContainer.h"


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
    //! エフェクト
    std::weak_ptr<effect::EffectContainer>_effect_container;
    //! エフェクト
    std::shared_ptr<ratchet::effect::EffectEmitter> _effect_emitter;
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
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="ptr"></param>
    std::shared_ptr<ratchet::effect::EffectEmitter> GetEffectEmitter(void) const;
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