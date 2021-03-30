#ifndef MY_VELOCITY_H
#define MY_VELOCITY_H


#include <Mof.h>


namespace my {
class Velocity {
private:
    //! 速度
    Mof::CVector3 _velocity;
    //! 角速度
    Mof::CVector3 _angular_velocity;
    //! 付与測度
    Mof::CVector3 _velocity_force;
    //! 付与測度
    Mof::CVector3 _angular_velocity_force;
    //! 減速Y
    float _gravity;
    //! 減速係数XZ
    float _drag;
    //! 減速係数
    float _angular_drag;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Velocity();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Velocity();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetVelocity(Mof::CVector3 value);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetVelocity(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetAngularVelocity(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetVelocityForce(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    void AddVelocityForce(Mof::CVector3 accele);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="accele"></param>
    void AddAngularVelocityForce(Mof::CVector3 accele);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    bool Update(float delta_time);
};
}
#endif // !MY_VELOCITY_H