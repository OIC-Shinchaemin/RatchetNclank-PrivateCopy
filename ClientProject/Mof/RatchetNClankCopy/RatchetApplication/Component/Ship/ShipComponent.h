#ifndef RATCHET_COMPONENT_SHIP_SHIP_COMPONENT_H
#define RATCHET_COMPONENT_SHIP_SHIP_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "../MotionComponent.h"


namespace ratchet {
namespace component {
namespace ship {
class ShipComponent : public component::UpdateComponent {
    using super = component::UpdateComponent;
private:
    //! モーション
    std::weak_ptr<component::MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<class ShipStateComponent> _state_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    ShipComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ShipComponent(const ShipComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ShipComponent();
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
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Activate(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<component::Component> Clone(void) override;
};
}
}
}
#endif // !RATCHET_COMPONENT_SHIP_SHIP_COMPONENT_H