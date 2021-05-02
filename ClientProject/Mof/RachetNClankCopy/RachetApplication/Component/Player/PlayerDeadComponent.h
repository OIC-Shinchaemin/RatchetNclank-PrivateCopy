#ifndef MY_PLAYER_DEAD_COMPONENT_H
#define MY_PLAYER_DEAD_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "My/Core/Timer.h"


namespace my {
class PlayerDeadComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! モーション
    std::weak_ptr<class MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! 状態
    //std::weak_ptr<class PlayerStateComponent> _state_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerDeadComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerDeadComponent(const PlayerDeadComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerDeadComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !MY_PLAYER_DEAD_COMPONENT_H