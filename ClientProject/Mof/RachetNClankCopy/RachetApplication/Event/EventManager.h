#ifndef MY_EVENT_MANAGER_H
#define MY_EVENT_MANAGER_H


namespace my {
class EventManager {
private:
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
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
};
}
#endif // !MY_EVENT_MANAGER_H