#ifndef MY_VELOCITY_COMPONENT_H
#define MY_VELOCITY_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>


namespace my {
class VelocityComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
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

    //virtual void InputMoveVelocity(float speed);
    //virtual void InputMoveAngularVelocity(float angle, float speed);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    VelocityComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    VelocityComponent(const VelocityComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~VelocityComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetVelocity(Mof::CVector3 value);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetGravity(float value);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetDrag(float value);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_VELOCITY_COMPONENT_H