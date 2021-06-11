#ifndef RATCHET_SHIP_LANDING_COMPONENT_H
#define RATCHET_SHIP_LANDING_COMPONENT_H


#include "ShipActionComponent.h"
#include "Base/Core/Observable.h"

#include "../../Camera/CameraController.h"


namespace ratchet {
class ShipLandingComponent : public ratchet::ShipActionComponent,
    public base::core::Observable<const ratchet::camera::CameraController::CameraInfo&> {
    using super = ratchet::ShipActionComponent;
    using Observable = base::core::Observable<const ratchet::camera::CameraController::CameraInfo&>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    ShipLandingComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ShipLandingComponent(const ShipLandingComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ShipLandingComponent();
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
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddObserver(const std::shared_ptr<base::core::Observer<const ratchet::camera::CameraController::CameraInfo&>>& ptr);
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
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_SHIP_LANDING_COMPONENT_H