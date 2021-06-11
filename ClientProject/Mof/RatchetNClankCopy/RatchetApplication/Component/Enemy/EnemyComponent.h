#ifndef RATCHET_ENEMY_COMPONENT_H
#define RATCHET_ENEMY_COMPONENT_H


#include "../CharacterComponent.h"

#include <optional>
#include <memory>

#include "Base/Core/Timer.h"


namespace ratchet {
class EnemyComponent : public ratchet::CharacterComponent {
    using super = ratchet::CharacterComponent;
private:
    //! 休止状態切り替え
    base::core::Timer _velocity_timer;
    //! 標的
    std::weak_ptr<ratchet::actor::Actor> _target;
    //! 速度
    std::weak_ptr<class VelocityComponent> _velocity_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyComponent(const EnemyComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<ratchet::actor::Actor>& ptr);
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
    std::weak_ptr<ratchet::actor::Actor> GetTarget(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::optional<Mof::CVector3> GetTargetPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetHomeDistance(void) const;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
};
}
#endif // !RATCHET_ENEMY_COMPONENT_H