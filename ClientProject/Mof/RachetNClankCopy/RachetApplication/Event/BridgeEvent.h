#ifndef MY_BRIDGE_EVENT_H
#define MY_BRIDGE_EVENT_H


#include "My/Core/Observer.h"
#include "My/Core/Observable.h"

#include <memory>
#include <vector>

#include "../Actor.h"
#include "../Stage/Stage.h"


namespace my {
class BridgeEvent :
    public std::enable_shared_from_this<my::BridgeEvent>,
    public my::Observer<const char*, const std::shared_ptr<my::Actor>&>,
    public my::Observable<const char*, const std::shared_ptr<my::BridgeEvent>&> {
    using Observable = my::Observable<const char*, const std::shared_ptr<my::BridgeEvent>&>;
private:
    //! �ʒm�A�N�^�[
    std::vector<std::shared_ptr<my::Actor>> _for_bridge_event_actors;
    //! �X�e�[�W
    Stage* _stage;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BridgeEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BridgeEvent();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetStage(Stage* ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddTriggerActor(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name=""></param>
    void AllDelete(void);
};
}
#endif // !MY_BRIDGE_EVENT_H