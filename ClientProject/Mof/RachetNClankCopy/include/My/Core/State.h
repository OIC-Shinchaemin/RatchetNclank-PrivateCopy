#ifndef MY_STATE_H
#define MY_STATE_H


#include <memory>


namespace my {
class State {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    State();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~State();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const = 0;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Update(float delta_time) = 0;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    virtual void Enter(void) = 0;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    virtual void Exit(void) = 0;
};
}
#endif // !MY_STATE_H