#ifndef MY_EVENT_H
#define MY_EVENT_H


#include "My/Core/Observable.h"

#include <memory>


namespace my {
class Event : public std::enable_shared_from_this<my::Event> {
protected:
    //! 通知用
    my::Observable<const char*, const std::shared_ptr<my::Event>&> _subject;
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
    my::Observable<const char*, const std::shared_ptr<my::Event>&>* GetSubject(void);
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
#endif // !MY_EVENT_H