#ifndef MY_SHIP_LANDING_COMPONENT_H
#define MY_SHIP_LANDING_COMPONENT_H


#include "ShipActionComponent.h"
#include "Base/Core/Observable.h"

#include "../../Camera/CameraController.h"


namespace my {
class ShipLandingComponent : public my::ShipActionComponent,
    public my::Observable<const my::CameraController::CameraInfo&> {
    using super = my::ShipActionComponent;
    using Observable = my::Observable<const my::CameraController::CameraInfo&>;
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
    void AddObserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr);
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
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
#endif // !MY_SHIP_LANDING_COMPONENT_H