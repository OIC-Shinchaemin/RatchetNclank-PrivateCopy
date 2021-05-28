#ifndef MY_EVENT_MANAGER_H
#define MY_EVENT_MANAGER_H


#include <memory>

#include "Event.h"


namespace my {
class EventManager : 
    public std::enable_shared_from_this<my::EventManager>,
    public my::Observer<const char*, const std::shared_ptr<my::Event>&> {
private:
    //! ゲームイベント
    std::vector<std::shared_ptr<my::Event>> _events;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EventManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EventManager();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Event>& ptr) override;
    /// <summary>
    /// 作成
    /// </summary>
    template<typename Event>
    std::shared_ptr<Event> CreateGameEvent(void) {
        auto ptr = std::make_shared<Event>();
        ptr->GetSubject()->AddObserver(shared_from_this());
        this->_events.push_back(ptr);
        return ptr;
    }
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InitializeGameEvent(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    //bool Update(float delta_time);
    bool UpdateGameEvent(float delta_time);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_EVENT_MANAGER_H