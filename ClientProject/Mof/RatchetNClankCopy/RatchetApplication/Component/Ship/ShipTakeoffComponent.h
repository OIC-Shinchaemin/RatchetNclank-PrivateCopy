#ifndef RATCHET_SHIP_TAKEOFF_COMPONENT_H
#define RATCHET_SHIP_TAKEOFF_COMPONENT_H


#include "ShipActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"


namespace ratchet {
class ShipTakeoffComponent : public ratchet::ShipActionComponent {
    using super = ratchet::ShipActionComponent;
private:
    //! タイマー
    base::core::Timer _timer;
    //! 上昇
    bool _takeoff;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    ShipTakeoffComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ShipTakeoffComponent(const ShipTakeoffComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ShipTakeoffComponent();
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
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
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
};
}
#endif // !RATCHET_SHIP_TAKEOFF_COMPONENT_H