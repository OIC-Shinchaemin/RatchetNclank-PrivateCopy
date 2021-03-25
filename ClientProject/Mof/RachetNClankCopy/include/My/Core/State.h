#ifndef MY_STATE_H
#define MY_STATE_H


#include <memory>


namespace my {
class State {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    State();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~State();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const = 0;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Update(float delta_time) = 0;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    virtual void Enter(void) = 0;
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    virtual void Exit(void) = 0;
};
}
#endif // !MY_STATE_H