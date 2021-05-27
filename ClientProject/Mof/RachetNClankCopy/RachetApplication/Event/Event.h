#ifndef MY_EVENT_H
#define MY_EVENT_H


#include <memory>


namespace my {
class Event : public std::enable_shared_from_this<my::Event> {
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