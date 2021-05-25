#ifndef MY_SHIP_EVENT_H
#define MY_SHIP_EVENT_H


#include "My/Core/Observer.h"

#include <memory>
#include <vector>

#include "Actor.h"
#include "BridgeEvent.h"


namespace my {
class ShipEvent :
    public std::enable_shared_from_this<my::ShipEvent>,
    public my::Observer<const char*, const std::shared_ptr<my::Actor>&>,
    public my::Observer<const char*, const std::shared_ptr<my::BridgeEvent>&> {
private:
    //! �ʒm�p
    my::Observable<const char*, const std::shared_ptr<my::Actor>& > _ship_event_subject;
    //! �ʒm�A�N�^�[
    //std::vector<std::shared_ptr<my::Actor>> _for_bridge_event_actors;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ShipEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ShipEvent();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::BridgeEvent>& ptr) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const char*, const std::shared_ptr<my::Actor>&>& GetShipEventSubject(void);
};
}
#endif // !MY_SHIP_EVENT_H