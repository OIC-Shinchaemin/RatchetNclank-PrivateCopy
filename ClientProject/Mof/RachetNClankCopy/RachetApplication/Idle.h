#ifndef MY_IDLE_H
#define MY_IDLE_H


#include "Action.h"

#include "Velocity.h"


namespace my {
class Idle : public my::Action {
    using super = my::Action;
private:
    //! 回転速度
    float _angular_speed;
    //! ラジアン
    float _ideal_angle;
    //! 速度
    my::Velocity* _velocity;

    virtual void InputMoveAngularVelocity(float angle, float speed);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool InactiveCondition(void) const override;
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Execute(float delta_time) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Idle();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Idle();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetVelocity(my::Velocity* ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetAngularSpeed(float speed);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="radian"></param>
    void SetIdealAngle(float radian);
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !MY_IDLE_H