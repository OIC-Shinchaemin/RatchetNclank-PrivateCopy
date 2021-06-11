#ifndef RATCHET_EVENT_H
#define RATCHET_EVENT_H


#include "Base/Core/Observable.h"

#include <memory>


namespace ratchet {
namespace event {
class Event : public std::enable_shared_from_this<ratchet::event::Event> {
protected:
    //! 通知用
    base::core::Observable<const char*, const std::shared_ptr<ratchet::event::Event>&> _subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Event();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Event();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const char*, const std::shared_ptr<ratchet::event::Event>&>* GetSubject(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
};
}
}
#endif // !RATCHET_EVENT_H