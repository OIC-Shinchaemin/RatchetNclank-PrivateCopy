#ifndef MY_PLAYER_H
#define MY_PLAYER_H


#include "Character.h"
#include "My/Core/Observer.h"

#include "../Weapon/Mechanical.h"


namespace my {
class Player : public my::Character, public my::Observer<std::shared_ptr<my::Mechanical>> {
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
        DamageDown,
        CountMax,
    };
private:
    //! 武器
    std::weak_ptr<my::Mechanical>_current_mechanical;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Player();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(std::shared_ptr<my::Mechanical> change) override;
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_PLAYER_H