#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"

#include "../SightRecognition.h"


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
enum class AIState {
    Patrol,
    Combat
};
class Enemy : public my::Character {
    using super = my::Character;
private:
    //! 標的
    std::weak_ptr<my::Character>_target;
    //std::vector< std::weak_ptr<my::Character>>_recognized;
    //! 視覚
    my::SightRecognition _sight;
    //! 状態
    my::AIState _state;
    //! 速度
    my::Velocity _velocity;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="rotate"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="position"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
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
    void SetTarget(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 視認可能判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 pos);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_ENEMY_H