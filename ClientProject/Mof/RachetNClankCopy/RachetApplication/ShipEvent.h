#ifndef MY_SHIP_EVENT_H
#define MY_SHIP_EVENT_H


#include "My/Core/Observer.h"

#include <memory>

#include "Actor.h"
#include "BridgeEvent.h"


namespace my {
class ShipEvent :
    public std::enable_shared_from_this<my::ShipEvent>,
    public my::Observer<const char*, const std::shared_ptr<my::Actor>&>,
    public my::Observer<const char*, const std::shared_ptr<my::BridgeEvent>&> {
private:
    //! 通知用
    my::Observable<const char*, const std::shared_ptr<my::Actor>& > _ship_event_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShipEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ShipEvent();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::BridgeEvent>& ptr) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const char*, const std::shared_ptr<my::Actor>&>& GetShipEventSubject(void);
};
}
#endif // !MY_SHIP_EVENT_H