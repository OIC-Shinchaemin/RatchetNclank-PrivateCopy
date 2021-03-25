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
    //! Œ»İ‚Ìó‘Ô
    std::shared_ptr<my::State>_current_state;
    //! Œ»İ‚Ìó‘Ô
    //std::vector<std::shared_ptr<my::State>> _stack;
    //! ‘JˆÚ‰Â”\‚Èó‘Ô
    std::unordered_map<std::string, std::shared_ptr<my::State>>_status;
public:
    /// <summary>
    /// ƒQƒbƒ^[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetCurrentStateName(void) const;
    /// <summary>
    /// “o˜^
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
    /// “o˜^
    /// </summary>
    /// <param name="ptr"></param>
    void RegisterState(const std::shared_ptr<my::State>& ptr);
    /// <summary>
    /// •ÏX
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
    /// <summary>
    /// ’Ç‰Á
    /// </summary>
    /// <param name="name"></param>
    //void PushState(const std::string& name);
    /// <summary>
    /// íœ
    /// </summary>
    /// <param name=""></param>
    //void PopState(void);
    /// <summary>
    /// XV
    /// </summary>
    /// <param name="delta_time"></param>
    void Update(float delta_time);
    /// <summary>
    /// ‰ğ•ú
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !MY_STATE_MACHINE_H