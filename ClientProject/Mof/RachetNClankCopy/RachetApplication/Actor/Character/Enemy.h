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
    //! 通知用
    my::Observable<const my::GameQuest&> _quest_subject;
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
    my::Observable<const my::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    //virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Render(void) override;
};
}
#endif // !MY_ENEMY_H