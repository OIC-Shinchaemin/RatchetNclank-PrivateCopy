#ifndef MY_STATE_MACHINE_H
#define MY_STATE_MACHINE_H


#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "My/Core/State.h"


namespace my {
class StateMachine {
private:
    //! 現在の状態
    std::shared_ptr<my::State>_current_state;
    //! 現在の状態
    //std::vector<std::shared_ptr<my::State>> _stack;
    //! 遷移可能な状態
    std::unordered_map<std::string, std::shared_ptr<my::State>>_status;
public:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetCurrentStateName(void) const;
    /// <summary>
    /// 登録
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <param name="...params"></param>
    template<typename T, typename... Args>
    void RegisterState(Args&&... params) {
        auto ptr = std::make_shared<T>(std::forward<Args>(params)...);
        _status.emplace(ptr->GetName(), ptr);
    }
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="ptr"></param>
    void RegisterState(const std::shared_ptr<my::State>& ptr);
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="name"></param>
    //void PushState(const std::string& name);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    //void PopState(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    void Update(float delta_time);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void Release(void);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    void DebugRender(void);
};
}
#endif // !MY_STATE_MACHINE_H