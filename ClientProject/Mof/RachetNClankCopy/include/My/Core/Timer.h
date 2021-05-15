#ifndef MY_TIMER_H
#define MY_TIMER_H


namespace my {
class Timer {
private:
    //! 時間
    float _time;
    //! 最大時間
    float _time_max;
    //! ループ
    bool _loop;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Timer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Timer();
    /// <summary>
    /// 現在の時間を返す
    /// </summary>
    float operator() (void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="max"></param>
    /// <param name="loop"></param>
    /// <returns></returns>
    void Initialize(float max, bool loop);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns>指定値に到達</returns>
    bool Tick(float delta_time);
};
}
#endif // !MY_TIMER_H