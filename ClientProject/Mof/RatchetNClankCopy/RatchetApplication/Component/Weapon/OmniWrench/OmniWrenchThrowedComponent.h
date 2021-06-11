#ifndef RATCHET_OMNI_WRENCH_THROWED_COMPONENT_H
#define RATCHET_OMNI_WRENCH_THROWED_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>


namespace ratchet {
class OmniWrenchThrowedComponent : public ratchet::ActionComponent {
    using super = ratchet::ActionComponent;
private:
    //! 遷移
    Mof::CVector3 _local_translate;
    //! 速さ
    float _move_speed;
    //! 移動した距離
    float _moved_distance;
    //! 閾値
    float _moved_distance_threshold;
    //! 進行方向
    Mof::CVector3 _ideal_move_direction;
    //! 所有者
    std::weak_ptr<ratchet::actor::Actor> _weapon_owner;
    //! 速度
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! 状態
    std::weak_ptr<class OmniWrenchActionStateComponent> _action_state_com;
    //! 衝突
    std::weak_ptr<class OmniWrenchCollisionComponent> _collision_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    OmniWrenchThrowedComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    OmniWrenchThrowedComponent(const OmniWrenchThrowedComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~OmniWrenchThrowedComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetWeaponOwner(const std::shared_ptr<ratchet::actor::Actor>& ptr);
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
    virtual std::string_view GetStateType(void) const override;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_OMNI_WRENCH_THROWED_COMPONENT_H