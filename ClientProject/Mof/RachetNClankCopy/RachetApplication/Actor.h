#ifndef MY_ACTOR_H
#define MY_ACTOR_H


#include <memory>
#include <string>

#include <Mof.h>

#include "My/Core/Define.h"


namespace my {
class Actor : public std::enable_shared_from_this<my::Actor> {
private:
    //! �g�����X�t�H�[��
    def::Transform _transform;
public:    
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Actor();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Actor();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector3 position);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="rotate"></param>
    void SetRotate(Mof::CVector3 rotate);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>���O</returns>
    std::string GetName(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPosition(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetRotate(void) const;
};
}
#endif // !MY_ACTOR_H