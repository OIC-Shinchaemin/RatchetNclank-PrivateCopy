#ifndef BASE_CORE_STATE_MACHINE_H
#define BASE_CORE_STATE_MACHINE_H


#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "State.h"


namespace base {
namespace core {
class StateMachine {
private:
    //! ���݂̏��
    std::shared_ptr<base::core::State>_current_state;
    //! ���݂̏��
    //std::vector<std::shared_ptr<base::core::State>> _stack;
    //! �J�ډ\�ȏ��
    std::unordered_map<std::string, std::shared_ptr<base::core::State>>_status;
public:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetCurrentStateName(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool EnableState(void) const;
    /// <summary>
    /// �o�^
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
    /// �o�^
    /// </summary>
    /// <param name="ptr"></param>
    void RegisterState(const std::shared_ptr<base::core::State>& ptr);
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="name"></param>
    //void PushState(const std::string& name);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name=""></param>
    //void PopState(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    void Update(float delta_time);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    void DebugRender(void);
};
}
}
#endif // !BASE_CORE_STATE_MACHINE_H